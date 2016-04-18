#ifndef VISITPROGRESSOBSERVER_H
#define VISITPROGRESSOBSERVER_H

class VisitProgressObserver {

public:    

	virtual void notifyGoDown(VTP_TreeP &tree) = 0;

	virtual void notifyGoUp(VTP_TreeP &tree) = 0;

};
#endif //VISITPROGRESSOBSERVER_H