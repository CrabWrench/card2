pipeline {
    agent any

    environment {
        // Настройки для компиляции
        CONFIGURATION = 'Release' // Или 'Debug' в зависимости от ваших нужд
        SOLUTION_FILE = 'card2.sln' // Имя вашего файла решения Visual Studio
    }

    stages {
        stage('Clone Repository') {
            steps {
                // Клонируем репозиторий из Git
                git url: 'https://github.com/CrabWrench/card2.git'
            }
        }
        
        stage('Build') {
            steps {
                script {
                    // Строим проект с использованием MSBuild
                    bat "\"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe\" ${SOLUTION_FILE} /p:Configuration=${CONFIGURATION}"
                }
            }
        }

        stage('Run Tests') {
            steps {
                script {
                    // Здесь добавьте команду для запуска ваших тестов (если есть)
                    // Например, если вы используете Google Test
                    bat 'C:\\GitHub\\card2\\x64\\card2.exe'
                }
            }
        }

    post {
        success {
            // Действия, которые выполняются при успешной сборке
            echo 'Сборка и тестирование прошли успешно!'
        }
        failure {
            // Действия, которые выполняются при сбое сборки
            echo 'Сборка завершилась с ошибками.'
        }
    }
}
