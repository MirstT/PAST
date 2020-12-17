#include "ServerDaemon.h"

#include <QtWidgets/QApplication>
#include <QVCore/QVCore.h>
#include "VMSCore/VMSUtil.h"

int main(int argc, char *argv[])
{
	::QVCoreInitialize("./CBBConfig.xml");
	IQUFile::CreateFilePath("d:\\vmsdb\\server", true);
	QVDBGAttachFile("d:\\vmsdb\\server\\dbg.txt");

	VMS_ENABLE_LOG(7);

    QApplication a(argc, argv);

    ServerDaemon w;
    w.show();
    int r= a.exec();
	QVCoreInvalidate();	
	return r;
}
