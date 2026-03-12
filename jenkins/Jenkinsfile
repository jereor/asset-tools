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

                    ./build/app/AssetTools --version
                '''
            }
        }
        stage("Validate Assets") {
            agent {
                docker {
                    image 'asset-tools-image'
                    reuseNode true
                }
            }
            steps {
                sh '''
                    ./build/app/AssetTools validate . --texture-config textures.yaml --audio-config audio.yaml
                '''
            }
        }
    }
}