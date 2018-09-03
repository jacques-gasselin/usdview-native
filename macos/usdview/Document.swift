//
//  USDDocument.swift
//  usdview
//
//  Created by Jacques Philippe Gasselin de Richebourg on 1/9/18.
//

import Cocoa

class Document: NSDocument {
    var stagePath: String = ""

    override func read(from url: URL, ofType _: String) throws {
        stagePath = url.path

        // We should wait to load until the Open dialogue is gone.
        // Otherwise debugging is a nightmare.
        DispatchQueue.main.async {
            self.openStage()
        }
    }

    func openStage() {
        _ = UsdStageInfo(stagePath: stagePath)
    }
}
