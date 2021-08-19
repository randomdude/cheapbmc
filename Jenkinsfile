//group=electronics
node("VS2017")
{
	deleteDir();
	checkout([
		$class: 'GitSCM', 
		branches: [[name: '*/master']], 
		doGenerateSubmoduleConfigurations: false, 
		extensions: [
			[$class: 'WipeWorkspace'], 
			[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: false, reference: '', trackingSubmodules: true]
		],
		submoduleCfg: [], 
		userRemoteConfigs: [[url: 'http://gitea/aliz/cheapbmc.git']]
	])

	// Set up vcpkg, which we will use to fetch libcurl
	dir("thirdparty/vcpkg")
	{
		bat "bootstrap-vcpkg.bat -disableMetrics"
		bat "vcpkg integrate install"
		bat "vcpkg --x86-windows install curl[tool] curl[openssl]"
		bat "vcpkg --x64-windows install curl[tool] curl[openssl]"
	}

	dir("code")
	{
		// Generate the config file, containing wifi details
		configFile = "#define CFG_WIFI_SSID \"foo\"\n"
		configFile += "#define CFG_WIFI_PASSWORD \"aaa\"\n"
		configFile += "static const char serverCert[] PROGMEM = R\"EOF()EOF\";\n"
		configFile += "static const char serverKey[] PROGMEM = R\"EOF()EOF\";\n"
		configFile += "static const char clientAuthCert[] PROGMEM = R\"EOF()EOF\";\n"
		writeFile file: 'config.h', text: configFile

		// Locate the vmbuild.exe file, which we will use to build the target under visual micro
		def codeDir = pwd()
		ideExtDir="C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\Common7\\IDE\\Extensions"
		dir(ideExtDir)
		{
			vmbuildPaths = findFiles(glob: '*\\VMBuild.exe')
		}
		assert(vmbuildPaths.length > 0) : "No visualmicro 'vmbuild.exe' found"

		// Finally, we can build the project.
		bat "\"${ideExtDir}\\${vmbuildPaths[0]}\" -builder.verbose=true -builder-close=true -builder.build=true -builder.output_directory=\"${codeDir}\\built\" -builder.rebuild=true -builder.upload=false  -builder.verbose_warnings=true -builder.project_path=\"${codeDir}\\panelctrl.vcxproj\" -builder.board_id=esp8266"
		archiveArtifacts artifacts: 'code\\built\\code.bin', onlyIfSuccessful: true
	}
}

node ("win10")
{
	deleteDir();
	checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [[$class: 'RelativeTargetDirectory', relativeTargetDir: 'kicad-jenkins-support']], submoduleCfg: [], userRemoteConfigs: [[url: 'http://gitea/aliz/kicad-jenkins-support']]])
	bat script: 'copy kicad-jenkins-support\\* .'

	def rootDir = pwd()
	def kicadSupport = load "${rootDir}\\build.groovy"
	kicadSupport.build("http://gitea/aliz/cheapbmc.git", "board")
}

