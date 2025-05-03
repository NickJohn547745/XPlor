#ifndef ZONEFILE_FACTORY_H
#define ZONEFILE_FACTORY_H

#include <QByteArray>
#include <memory>

class ZoneFile;

class ZoneFileFactory {
public:
    static std::shared_ptr<ZoneFile> Create(const QByteArray& data) {
        return nullptr;
    }

private:
};

#endif // ZONEFILE_FACTORY_H
