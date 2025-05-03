#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _qt_qml_online_minesweeper_final_Main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_online_minesweeper_final_Cell_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_online_minesweeper_final_CellLogic_js { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_online_minesweeper_final_BoardLogic_js { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_online_minesweeper_final_Board_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_online_minesweeper_final_LandingPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_online_minesweeper_final_StartSessionPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_online_minesweeper_final_JoinSessionPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_online_minesweeper_final_BoardPage_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/online_minesweeper_final/Main.qml"), &QmlCacheGeneratedCode::_qt_qml_online_minesweeper_final_Main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/online_minesweeper_final/Cell.qml"), &QmlCacheGeneratedCode::_qt_qml_online_minesweeper_final_Cell_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/online_minesweeper_final/CellLogic.js"), &QmlCacheGeneratedCode::_qt_qml_online_minesweeper_final_CellLogic_js::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/online_minesweeper_final/BoardLogic.js"), &QmlCacheGeneratedCode::_qt_qml_online_minesweeper_final_BoardLogic_js::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/online_minesweeper_final/Board.qml"), &QmlCacheGeneratedCode::_qt_qml_online_minesweeper_final_Board_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/online_minesweeper_final/LandingPage.qml"), &QmlCacheGeneratedCode::_qt_qml_online_minesweeper_final_LandingPage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/online_minesweeper_final/StartSessionPage.qml"), &QmlCacheGeneratedCode::_qt_qml_online_minesweeper_final_StartSessionPage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/online_minesweeper_final/JoinSessionPage.qml"), &QmlCacheGeneratedCode::_qt_qml_online_minesweeper_final_JoinSessionPage_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/online_minesweeper_final/BoardPage.qml"), &QmlCacheGeneratedCode::_qt_qml_online_minesweeper_final_BoardPage_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_apponline_minesweeper_final)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_apponline_minesweeper_final))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_apponline_minesweeper_final)() {
    return 1;
}
