//group=electronics

parallel(
'VS': 
{ 
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
			bat "vcpkg --triplet=x86-windows install curl[tool] curl[openssl] openssl"
			bat "vcpkg --triplet=x64-windows install curl[tool] curl[openssl] openssl"
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
			// Build both debug and release
			[ 'Release', 'Debug' ].each { $buildcfg ->
				bat "mkdir nuget\\lib\\Net45\\${$buildcfg}"
				// Do 32 and 64-bit builds
				[ 'x86', 'x64' ].each { $arch ->
					// Do the build..
					bat "\"${tool 'VS2017'}\" code.sln /p:Configuration=${$buildcfg} /p:Platform=\"${$arch}\" /p:ProductVersion=1.0.0.${env.BUILD_NUMBER}"
					bat "mkdir nuget\\runtimes\\${$arch}\\${$buildcfg}"

					// Copy the arch-independent cheapbmc_net assembly
					bat "copy /y Win32_anycpu\\${$buildcfg}\\cheapbmc_net.dll nuget\\lib\\Net45\\${$buildcfg}\\"

					// Copy these native files into the 'runtimes' directory.
					bat "copy /y ${$arch}\\${$buildcfg}\\*.dll nuget\\runtimes\\${$arch}\\${$buildcfg}\\"
				}
			}
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
},
'win10vs2017': 
{
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
})