import Foundation

enum SdfPathType {
    case primPath
    case propertyPath
}

struct SdfPath {
    let pathType : SdfPathType
    internal let components : [String]
    
    init (rawString : String, isPrimPath: Bool) {
        let pathType : SdfPathType
        if isPrimPath {
            pathType = SdfPathType.primPath
        } else {
            pathType = SdfPathType.propertyPath
        }
        
        self.init (rawString: rawString, pathType: pathType)
    }
    
    init (rawString: String, pathType: SdfPathType) {
        self.pathType = pathType
        self.components = rawString.split(separator: "/").map { String($0) }
    }
    
    init (components: [String], pathType: SdfPathType) {
        self.pathType = pathType
        self.components = components
    }
    
    func isPseudoRootPath() -> Bool {
        return self.components.count == 0
    }
    
    func getParentPath() -> (Bool, SdfPath) {
        if !isPseudoRootPath() {
            return (true, SdfPath(components: [String](self.components.dropLast()),
                                  pathType: self.pathType))
        }
        
        return (false, self)
    }
    
    func getName() -> String {
        if isPseudoRootPath() {
            return ""
        }
        
        return components.last!
    }
    
    func getDepth() -> Int {
        return components.count
    }
}

enum UsdPrimType {
    // TODO: Fill out with remaining types
    case mesh
    case xform
    case untyped
    
    init (rawString: String) {
        switch rawString {
        case "Mesh":
            self = .mesh
        case "Xform":
            self = .xform
        default:
            self = .untyped
        }
    }
}

struct UsdPrimInfo {
    let name : String
    let path : SdfPath
    let type : UsdPrimType
    let depth : Int
    
    init (path: SdfPath, type: UsdPrimType) {
        self.path = path
        self.name = path.getName()
        self.depth = path.getDepth()
        self.type = type
    }
}

enum UsdStageInterpolation {
    case held
    case linear
}

struct UsdStageInfo {
    let startTimeCode : Double
    let endTimeCode : Double
    let timeCodesPerSecond : Double
    let interpolationType : UsdStageInterpolation
    internal let ptr : UnsafeMutableRawPointer
    
    init (stagePath: String) {
        ptr = _openStage(stagePath)
        startTimeCode = _getStartTimeCode(ptr)
        endTimeCode = _getEndTimeCode(ptr)
        timeCodesPerSecond = _getTimeCodesPerSecond(ptr)
        
        let interpStr = String(cString: _getInterpolationType(ptr))
        if interpStr == "Held" {
            interpolationType = UsdStageInterpolation.held
        } else {
            interpolationType = UsdStageInterpolation.linear
        }
    }
    
    func getPrims() -> [UsdPrimInfo] {
        var numPrims : Int32 = 0
        var result : [UsdPrimInfo] = []
        var stream = _getPrimInfo(self.ptr, &numPrims)!;
        
        let getString = { (s: inout UnsafeMutablePointer<UnsafePointer<Int8>?>) -> String in
            if let n = s.pointee { s += 1; return String(cString: n) }
            return ""
        }
        
        for _ in 0..<numPrims {
            let path = getString(&stream)
            let type = getString(&stream)
            
            result.append(UsdPrimInfo(path: SdfPath(rawString: path,
                                                    isPrimPath: true),
                                      type: UsdPrimType(rawString: type)))
        }
        
        return result
    }
    
    func reload() {
        _reloadStage(ptr)
    }
}
