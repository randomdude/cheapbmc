//group=electronics
node ("win10")
{
  deleteDir();
  checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [[$class: 'RelativeTargetDirectory', relativeTargetDir: 'kicad-jenkins-support']], submoduleCfg: [], userRemoteConfigs: [[url: 'http://gitea/aliz/kicad-jenkins-support']]])
  bat script: 'copy kicad-jenkins-support\\* .'

  def rootDir = pwd()
  def kicadSupport = load "${rootDir}\\build.groovy"
  kicadSupport.build("http://gitea/aliz/cheapbmc.git", "board")
}

node("VS2017")
{
	deleteDir();
	checkout scm;

	dir("code")
	{
		bat "\"${tool 'VS2017'}\" panelctrl.sln /p:Configuration=Debug /p:Platform=\"x86\" /p:ProductVersion=1.0.0.${env.BUILD_NUMBER}"
		archiveArtifacts artifacts: 'Debug\panelctrl.bin', onlyIfSuccessful: true
	}
}