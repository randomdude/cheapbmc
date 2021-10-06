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
	bat "powershell -executionpolicy bypass -File initSettings.ps1"
	stage("Fetching nuget packages")
	{
		dir ('code')
		{
			bat 'nuget restore'
		}
	}

	stage("Setting up curl via vcpkg")
	{
		// Set up vcpkg, which we will use to fetch libcurl
		dir("thirdparty/vcpkg")
		{
			bat "bootstrap-vcpkg.bat -disableMetrics"
			bat "vcpkg integrate install"
			bat "vcpkg --triplet=x86-windows install curl[tool] curl[openssl]"
			bat "vcpkg --triplet=x64-windows install curl[tool] curl[openssl]"
		}
	}

	dir("code")
	{
		bat "powershell -executionpolicy bypass -File setproperty.ps1 -Filename tests\\app.config -settingname checkoutDir -newval \"${WORKSPACE}\""

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

		stage("Building uC code")
		{
			// Finally, we can build the project, via VSMicro.
			bat "\"${ideExtDir}\\${vmbuildPaths[0]}\" -builder.verbose=true -builder-close=true -builder.build=true -builder.output_directory=\"${codeDir}\\built\" -builder.rebuild=true -builder.upload=false  -builder.verbose_warnings=true -builder.project_path=\"${codeDir}\\code.vcxproj\" -builder.board_id=esp8266"
			archiveArtifacts artifacts: 'built\\code.bin', onlyIfSuccessful: true
		}

		// For now, we don't run tests, since they require an esp8266 board we can talk to via wifi.

		// Now we build the host-side tools via VS as normal.
		stage("Building host-side code tooling..")
		{
			bat "\"${tool 'VS2017'}\" code.sln /p:Configuration=Debug   /p:Platform=\"x86\" /p:ProductVersion=1.0.0.${env.BUILD_NUMBER}"
			bat "\"${tool 'VS2017'}\" code.sln /p:Configuration=Release /p:Platform=\"x86\" /p:ProductVersion=1.0.0.${env.BUILD_NUMBER}"
			bat "\"${tool 'VS2017'}\" code.sln /p:Configuration=Debug   /p:Platform=\"x64\" /p:ProductVersion=1.0.0.${env.BUILD_NUMBER}"
			bat "\"${tool 'VS2017'}\" code.sln /p:Configuration=Release /p:Platform=\"x64\" /p:ProductVersion=1.0.0.${env.BUILD_NUMBER}"

			bat "mkdir nuget\\lib\\Net45\\Debug"
			bat "mkdir nuget\\lib\\Net45\\Release"
			bat "mkdir nuget\\runtimes\\x64\\Release"
			bat "mkdir nuget\\runtimes\\x86\\Release"

			bat "xcopy /e Win32_anycpu\\Debug\\cheapbmc_net.dll nuget\\lib\\Net45\\Debug\\"
			bat "xcopy /e Win32_anycpu\\Release\\cheapbmc_net.dll nuget\\lib\\Net45\\Release\\"

			bat "xcopy /e Win32_anycpu\\Debug\\libCurl.dll Win32_anycpu\\Debug\\libCurlShim.dll Win32\\Debug\\*.dll nuget\\runtimes\\x86\\Debug\\"
			bat "xcopy /e Win32_anycpu\\Debug\\libCurl.dll Win32_anycpu\\Debug\\libCurlShim.dll x64\\Debug\\*.dll nuget\\runtimes\\x64\\Debug\\"
			bat "xcopy /e Win32_anycpu\\Release\\libCurl.dll Win32_anycpu\\Release\\libCurlShim.dll Win32\\Release\\*.dll nuget\\runtimes\\x86\\Debug\\"
			bat "xcopy /e Win32_anycpu\\Release\\libCurl.dll Win32_anycpu\\Release\\libCurlShim.dll x64\\Release\\*.dll nuget\\runtimes\\x64\\Debug\\"
		}

		stage("Publishing artifacts")
		{
			// Build the nuget package.
			dir("nuget")
			{
				bat "nuget pack -Version 1.0.${BUILD_NUMBER}"
			
				// Archive locally and send to the nuget server
				archiveArtifacts artifacts: '*.nupkg'
				bat "nuget push -Source http://nuget/v3/index.json *.nupkg"
			}
		}
	}
}

node ("win10")
{
	stage("Checking board via KiCAD")
	{
		deleteDir();
		checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [[$class: 'RelativeTargetDirectory', relativeTargetDir: 'kicad-jenkins-support']], submoduleCfg: [], userRemoteConfigs: [[url: 'http://gitea/aliz/kicad-jenkins-support']]])
		bat script: 'copy kicad-jenkins-support\\* .'

		def rootDir = pwd()
		def kicadSupport = load "${rootDir}\\build.groovy"
		kicadSupport.build("http://gitea/aliz/cheapbmc.git", "board")
	}
}
