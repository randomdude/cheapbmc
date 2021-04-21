//group=electronics
node ("win10")
{
  dir("board")
  {
    checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [[$class: 'RelativeTargetDirectory', relativeTargetDir: 'kicad-jenkins-support']], submoduleCfg: [], userRemoteConfigs: [[url: 'http://gitea/aliz/kicad-jenkins-support']]])
    bat script: 'copy kicad-jenkins-support\\* .'

    def rootDir = pwd()
    def kicadSupport = load "${rootDir}\\build.groovy"
    kicadSupport.build("http://gitea/aliz/cheapbmc.git")
  }
}