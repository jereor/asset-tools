pipeline {
    agent any

    stages {
        stage('Build Image') {
            steps {
                script {
                    dockerImage = docker.build('asset-tools-image')
                }
            }
        }

        stage('Build App') {
            agent {
                docker {
                    image 'asset-tools-image'
                    reuseNode true
                }
            }
            steps {
                sh '''
                    git --version
                    gcc --version
                    cmake --version

                    pwd
                    ls -la

                    ./scripts/build.sh

                    cd build
                    ls -la

                    cd app
                    ls -la

                    ./AssetTools --help
                '''
            }
        }
    }
}