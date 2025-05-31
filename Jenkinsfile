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
                    bat "\"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe\" ${SOLUTION_FILE} /p:Configuration=${CONFIGURATION}"
                }
            }
        }

        stage('Run Tests') 
        {
            steps {
                script {
                    bat 'cd build\\${CONFIGURATION} && card2.exe'
                }
            }
        }
    }
}

