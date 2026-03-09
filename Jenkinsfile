pipeline {
    agent any

    stages {
        stage('Build') {
            agent {
                docker {
                    image 'ams21/cmake:4.2.1'
                    reuseNode true
                }
            }
            steps {
                sh '''
                    pwd
                    ls -la
                    
                    gcc --version
                    cmake --version

                    cd scripts
                    ls -la
                    ./build.sh

                    cd ..
                    ls -la

                    cd build
                    ls -la

                    cd app
                    ls -la

                    cd Release
                    ls -la

                    ./AssetTools.exe --help
                '''
            }
        }
    }
}
