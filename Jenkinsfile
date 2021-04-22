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
		def codeDir = pwd()
		bat "\"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\Extensions\opspbqse.n3l\VMBuild.exe\" -builder.verbose=true -builder.build=true -builder.rebuild=true -builder.upload=false  -builder.verbose_warnings=true -builder.project_path=\"${codeDir}\panelctrl.vcxproj\" -builder.board_id=esp8266"
		archiveArtifacts artifacts: 'Debug/panelctrl.bin', onlyIfSuccessful: true
	}
}