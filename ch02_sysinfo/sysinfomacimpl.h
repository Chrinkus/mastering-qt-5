#ifndef SYSINFOMACIMPL_H
#define SYSINFOMACIMPL_H

#include "sysinfo.h"

#include <QtGlobal>
#include <QVector>

class SysInfoMacImpl : public SysInfo
{
private:
    QVector<qulonglong> mCpuLoadLastValues;
public:
    SysInfoMacImpl();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private:
    QVector<qulonglong> cpuRawData();
};

#endif // SYSINFOMACIMPL_H
