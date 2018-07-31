import qbs

Product {
	type: "staticlibrary"
    name: "Plurq"
	Depends { name: "cpp" }

	files: ["*.cpp", "*.h"]
	Export {
		Depends { name: "cpp" }
		cpp.includePaths: [product.sourceDirectory]
	}
}
