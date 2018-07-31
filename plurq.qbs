import qbs

StaticLibrary {
    name: "Plurq"
    Depends { name: "cpp" }
    Depends {
        name: "Qt"
        submodules: ["core", "gui", "network", "networkauth"]
    }

    files: ["*.cpp", "*.h"]
    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [product.sourceDirectory]
	}
}
