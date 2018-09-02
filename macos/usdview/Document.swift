//
//  USDDocument.swift
//  usdview
//
//  Created by Jacques Philippe Gasselin de Richebourg on 1/9/18.
//

import Cocoa

class Document: NSDocument {
    override func read(from url: URL, ofType typeName: String) throws {
        let stagePath = url.path
        let info = UsdStageInfo(stagePath: stagePath)
    }
}
