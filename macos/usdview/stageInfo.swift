import Foundation

struct UsdPrimInfo {
    let name : String
    let path : String
    let type : String
    let depth : Int
}

func getPrims(stagePath: String) -> [UsdPrimInfo] {
    var numPrims : Int32 = 0
    var result : [UsdPrimInfo] = []
    var stream = _getPrimInfo(stagePath, &numPrims)!;
    
    let getString = { (s: inout UnsafeMutablePointer<UnsafePointer<Int8>?>) -> String in
        if let n = s.pointee { s += 1; return String(cString: n) }
        return ""
    }
    
    let getInt = { (s: inout UnsafeMutablePointer<UnsafePointer<Int8>?>) -> Int in
        if let n = s.pointee { s += 1; return Int(bitPattern: n) }
        return 0
    }
    
    for _ in 0..<numPrims {
        let name = getString(&stream)
        let path = getString(&stream);
        let type = getString(&stream)
        let depth = getInt(&stream)
        
        result.append(UsdPrimInfo(name: name, path: path,
                                  type: type, depth: depth))
    }
    
    return result
}
