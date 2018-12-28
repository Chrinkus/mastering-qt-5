#ifndef SYSINFOLINUXIMPL_H
#define SYSINFOLINUXIMPL_H

#include <QtGlobal>
#include <QVector>

#include "sysinfo.h"

class SysInfoLinuxImpl : public SysInfo {
private:
    QVector<qulonglong> mCpuLoadLastValues;

public:
    SysInfoLinuxImpl();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private:
    QVector<qulonglong> cpuRawData();
};

#endif // SYSINFOLINUXIMPL_H
