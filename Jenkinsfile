pipeline {
    agent any

    stages {
        stage('Build') {
            agent {
                docker {
                    image 'luxel/alpine-cmake:latest'
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
