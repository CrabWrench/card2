pipeline 
{
    agent any

    environment
    {
        MSBUILD = "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe"
        SOLUTION_FILE = 'card2.sln'
    }

    stages {
        stage('Checkout') {
            steps {
                git url: 'https://github.com/CrabWrench/card2.git', 
                     branch: 'main', 
                     credentialsId: 'GITHUB_CREDS' // Создайте в Jenkins Credentials для GitHub
            }
        }

        stage('Build') {
            steps {
                bat "\"${MSBUILD}\" ${SOLUTION} /p:Configuration=Release /p:Platform=x64"
            }
            post {
                success {
                    archiveArtifacts artifacts: '**/bin/x64/Release/*.exe', // Архивация результатов
                                allowEmptyArchive: false
                }
            }
        }

        stage('Test') {
            steps {
                // Пример запуска тестов (если есть)
                bat '"**/bin/x64/Release/*_tests.exe" --gtest_output=xml:test_results.xml'
            }
            post {
                always {
                    junit 'test_results.xml' // Публикация результатов тестов
                }
            }
        }
    }

    post {
        failure {
            emailext body: 'Сборка ${BUILD_URL} завершилась с ошибкой',
                     subject: 'FAILED: Job ${JOB_NAME}',
                     to: 'your@email.com'
        }
    }
}
