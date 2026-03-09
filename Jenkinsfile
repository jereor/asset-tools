pipeline {
    agent any

    stages {
        stage('Build') {
            agent {
                docker {
                    image 'ams21/cmake:4.2.1'
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
