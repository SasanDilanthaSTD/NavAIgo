#ifndef IAGENT_H
#define IAGENT_H

#include <QString>
#include <QJsonObject>

// Interface for all agents in the syst
class IAgent{
public:
    virtual ~IAgent() = default;

    // Every agent must process a task and return a structured JSON response
    virtual QJsonObject processTask(const QString input) = 0;

};

#endif // IAGENT_H
