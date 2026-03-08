pipeline {
    agent any

    stages {
        stage('Docker Test') {
            agent {
                docker {
                    image 'kitware/cmake:ci-debian13-x86_64-2026-02-08'
                }
            }
            steps {
                sh 'echo "Test With Docker"'
            }
        }
    }
}
