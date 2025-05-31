pipeline 
{
    agent any

    environment
    {
        CONFIGURATION = 'Release'
        SOLUTION_FILE = 'card2.sln'
    }

    stages
    {
        stage('Clone Repository')
        {
            steps {
                git url: 'https://github.com/CrabWrench/card2'
            }
        }
        
        stage('Build')
        {
            steps {
                script {
                    bat 'C:\ProgramData\Jenkins\.jenkins\workspace\HEAVEN_OR_HELL>card2.sln /p:Configuration=Release'
                }
            }
        }

        stage('Run Tests') 
        {
            steps {
                script {
                    bat 'cd build\\${CONFIGURATION}'
                    bat 'card2.exe'
                }
            }
        }
    }
}

