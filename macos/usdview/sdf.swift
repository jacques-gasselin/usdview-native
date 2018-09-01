import Foundation

enum SdfPathType {
    case primPath
    case propertyPath
}

struct SdfPath {
    let pathType: SdfPathType
    internal let components: [String]

    init(rawString: String, isPrimPath: Bool) {
        let pathType: SdfPathType
        if isPrimPath {
            pathType = SdfPathType.primPath
        } else {
            pathType = SdfPathType.propertyPath
        }

        self.init(rawString: rawString, pathType: pathType)
    }

    init(rawString: String, pathType: SdfPathType) {
        self.pathType = pathType
        components = rawString.split(separator: "/").map { String($0) }
    }

    init(components: [String], pathType: SdfPathType) {
        self.pathType = pathType
        self.components = components
    }

    func isPseudoRootPath() -> Bool {
        return components.count == 0
    }

    func getParentPath() -> (Bool, SdfPath) {
        if !isPseudoRootPath() {
            return (true, SdfPath(components: [String](components.dropLast()),
                                  pathType: pathType))
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

    func getString() -> String {
        return "/" + components.joined(separator: "/")
    }
}
