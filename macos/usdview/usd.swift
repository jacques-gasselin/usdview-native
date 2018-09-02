import Foundation

enum UsdPrimType {
    case mesh
    case xform
    case untyped

    init(rawString: String) {
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
    let name: String
    let path: SdfPath
    let type: UsdPrimType
    let depth: Int

    init(path: SdfPath, type: UsdPrimType) {
        self.path = path
        name = path.getName()
        depth = path.getDepth()
        self.type = type
    }
}

enum UsdStageInterpolation {
    case held
    case linear
}

struct UsdStageInfo {
    let startTimeCode: Double
    let endTimeCode: Double
    let timeCodesPerSecond: Double
    let interpolationType: UsdStageInterpolation
    internal let ptr: UnsafeMutableRawPointer

    init(stagePath: String) {
        ptr = usdffi_openStage(stagePath)
        startTimeCode = usdffi_getStartTimeCode(ptr)
        endTimeCode = usdffi_getEndTimeCode(ptr)
        timeCodesPerSecond = usdffi_getTimeCodesPerSecond(ptr)

        let interpStr = String(cString: usdffi_getInterpolationType(ptr))
        if interpStr == "Held" {
            interpolationType = UsdStageInterpolation.held
        } else {
            interpolationType = UsdStageInterpolation.linear
        }
    }

    func getPrims() -> [UsdPrimInfo] {
        var numPrims: Int32 = 0
        var result: [UsdPrimInfo] = []
        var stream = usdffi_getPrimInfo(ptr, &numPrims)!

        let getString = { (ptr: inout UnsafeMutablePointer<UnsafePointer<Int8>?>) -> String in
            if let raw = ptr.pointee { ptr += 1; return String(cString: raw) }
            return ""
        }

        for _ in 0 ..< numPrims {
            let path = getString(&stream)
            let type = getString(&stream)

            result.append(UsdPrimInfo(path: SdfPath(rawString: path,
                                                    isPrimPath: true),
                                      type: UsdPrimType(rawString: type)))
        }

        return result
    }

    func reload() {
        usdffi_reloadStage(ptr)
    }

    func setDefaultPrim(path: SdfPath) {
        usdffi_setDefaultPrim(ptr, path.getString())
    }

    func getDefaultPrim() -> String {
        return String(cString: usdffi_getDefaultPrim(ptr))
    }
}
