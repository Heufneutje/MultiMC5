#include "MultiMC.h"
#include "gui/MainWindow.h"

// Crash handling
#ifdef HANDLE_SEGV
#include <HandleCrash.h>
#endif

#include "gui/dialogs/TasksDialog.h"

int main_gui(MultiMC &app)
{
	// show main window
	QIcon::setThemeName(MMC->settings()->get("IconTheme").toString());
	MainWindow mainWin;
	mainWin.restoreState(QByteArray::fromBase64(MMC->settings()->get("MainWindowState").toByteArray()));
	mainWin.restoreGeometry(QByteArray::fromBase64(MMC->settings()->get("MainWindowGeometry").toByteArray()));
	mainWin.show();
	mainWin.checkMigrateLegacyAssets();
	mainWin.checkSetDefaultJava();
	mainWin.checkInstancePathForProblems();

	TasksDialog dlg;
	dlg.resize(640, 480);
	dlg.show();

	return app.exec();
}

int main(int argc, char *argv[])
{
	// initialize Qt
	MultiMC app(argc, argv);

	Q_INIT_RESOURCE(instances);
	Q_INIT_RESOURCE(multimc);
	Q_INIT_RESOURCE(backgrounds);
	Q_INIT_RESOURCE(versions);

#ifdef HANDLE_SEGV
	// Register signal handler for generating crash reports.
	initBlackMagic();
#endif
	Q_INIT_RESOURCE(pe_dark);
	Q_INIT_RESOURCE(pe_light);

	switch (app.status())
	{
	case MultiMC::Initialized:
		return main_gui(app);
	case MultiMC::Failed:
		return 1;
	case MultiMC::Succeeded:
		return 0;
	}
}
