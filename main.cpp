#include <QGuiApplication>
#include <QProcess>
#include <QDebug>
#include <QRegularExpression>

int main(int a, char **b)
{
    QGuiApplication app(a, b);

    QProcess p;
    p.start("c:\\d\\installation\\msys2\\usr\\bin\\ssh-agent.EXE");
    p.waitForFinished();
    QString output(p.readAllStandardOutput());
    output = output.replace('\n', " ");

    QRegularExpression re("SSH_AUTH_SOCK=(.*?);.*Agent pid (.*);");
    QRegularExpressionMatch match = re.match(output);
    if (match.hasMatch()) {
        QString path = "c:\\d\\installation\\msys2\\" + match.captured(1);
        qputenv("SSH_AUTH_SOCK", path.toLatin1());
        qputenv("SSH_AGENT_PID", match.captured(2).toLatin1());
        QProcess::startDetached("C:\\d\\installation\\cmder\\cmder.exe");
        return 0;
    } else {
        return 1;
    }
}
