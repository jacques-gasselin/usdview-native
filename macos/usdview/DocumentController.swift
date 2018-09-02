//
//  DocumentController.swift
//  usdview
//
//  Created by Jacques Philippe Gasselin de Richebourg on 1/9/18.
//

import Cocoa

class DocumentController: NSDocumentController {
    override func beginOpenPanel(_ openPanel: NSOpenPanel, forTypes inTypes: [String]?, completionHandler: @escaping (Int) -> Void) {
        var types: [String] = []

        if let inTypes = inTypes {
            types.append(contentsOf: inTypes)
        }

        // This is temporary until we figure out why the UTIs are not working
        // with the CFDocumentTypes declaration
        if types.count < 1 {
            types.append("usd")
            types.append("usda")
            types.append("usdc")
            types.append("usdz")
        }

        super.beginOpenPanel(openPanel, forTypes: types, completionHandler: completionHandler)
    }

    override func documentClass(forType _: String) -> AnyClass? {
        return Document.self
    }
}
