#include "Settings.h"
#include "ui_Settings.h"

#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QVariant>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    m_fileName = "Settings.xml";
    ui->setupUi(this);
    fromXml();
}

Settings::~Settings()
{
    delete ui;
}

int Settings::getPc()
{
    return ui->spinBoxPc->value();
}

int Settings::getProductMin()
{
    return ui->spinBoxProductMin->value();
}

int Settings::getProductMax()
{
    return ui->spinBoxProductMax->value();
}

int Settings::getSellerMin()
{
    return ui->spinBoxSellerMin->value();
}

int Settings::getSellerMax()
{
    return ui->spinBoxSellerMax->value();
}

void Settings::setPc(int value)
{
    ui->spinBoxPc->setValue(value);
}

void Settings::setProductMin(int value)
{
    ui->spinBoxProductMin->setValue(value);
}

void Settings::setProductMax(int value)
{
    ui->spinBoxProductMax->setValue(value);
}

void Settings::setSellerMin(int value)
{
    ui->spinBoxSellerMin->setValue(value);
}

void Settings::setSellerMax(int value)
{
    ui->spinBoxSellerMax->setValue(value);
}

bool Settings::fromXml()
{
    QFile file(m_fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    QXmlStreamReader xml(&file);

    if (!xml.readNextStartElement())
    {
        return false;
    }

    if (xml.name() != "TuKiBazarSettings")
    {
        return false;
    }

    while (xml.readNextStartElement())
    {
        if (xml.name() == "Pc")
        {
            setPc(QVariant(xml.readElementText()).toInt());
        }
        else if (xml.name() == "SellerMin")
        {
            setSellerMin(QVariant(xml.readElementText()).toInt());
        }
        else if (xml.name() == "SellerMax")
        {
            setSellerMax(QVariant(xml.readElementText()).toInt());
        }
        else if (xml.name() == "ProductMin")
        {
            setProductMin(QVariant(xml.readElementText()).toInt());
        }
        else if (xml.name() == "ProductMax")
        {
            setProductMax(QVariant(xml.readElementText()).toInt());
        }
        else
        {
            xml.skipCurrentElement();
        }
    }

    /*if (!xml.readNextStartElement())
    {
        return false;
    }

    if (xml.name() != "ViAuthorisationMain")
    {
        return;
    }

    clearAllData();

    QXmlStreamAttributes streamAttributes = xml.attributes();
    m_lastChangeMain = ViAuthorisationConversions::qStringToQDateTime(streamAttributes.value("lastChange").toString());
    m_version    = ViAuthorisationConversions::qStringToInt(streamAttributes.value("version").toString());

    while (xml.readNextStartElement())
    {
        if (xml.name() == "IP-Address")
        {
            m_ip = xml.readElementText();
        }
        else if (xml.name() == "AllowFallBackToLocalAuthentication")
        {
            m_allowFallBackToLocalAuthentication = ViAuthorisationConversions::qStringToBool(xml.readElementText());
        }
        else if (xml.name() == "UserConfigFilePath")
        {
            m_userConfigurationFilePath = xml.readElementText();
        }
        else if (xml.name() == "RoleConfigFilePath")
        {
            m_roleConfigurationFilePath = xml.readElementText();
        }
        else if (xml.name() == "ComputerGroupConfigFilePath")
        {
            m_computerGroupConfigurationFilePath = xml.readElementText();
        }
        else if (xml.name() == "policies")
        {
            QXmlStreamAttributes streamAttributes = xml.attributes();
            QDateTime lastChange = ViAuthorisationConversions::qStringToQDateTime(streamAttributes.value("lastChange").toString());

            while (xml.readNextStartElement())
            {
                if (xml.name() == "history")
                {
                    QXmlStreamAttributes streamAttributes = xml.attributes();
                    m_policies.setPasswordHistoryNum(ViAuthorisationConversions::qStringToInt(streamAttributes.value("num").toString()));
                    m_policies.setPasswordHistory(ViAuthorisationConversions::qStringToBool(xml.readElementText()));
                }
                else if (xml.name() == "blockAfterFail")
                {
                    QXmlStreamAttributes streamAttributes = xml.attributes();
                    m_policies.setBlockAfterFailNum(ViAuthorisationConversions::qStringToInt(streamAttributes.value("num").toString()));
                    m_policies.setBlockAfterFail(ViAuthorisationConversions::qStringToBool(xml.readElementText()));
                }
                else if (xml.name() == "automaticLogout")
                {
                    QXmlStreamAttributes streamAttributes = xml.attributes();
                    m_policies.setAutomaticLogoutNum(ViAuthorisationConversions::qStringToInt(streamAttributes.value("num").toString()));
                    m_policies.setAutomaticLogout(ViAuthorisationConversions::qStringToBool(xml.readElementText()));
                }
                else if (xml.name() == "passwordChanges")
                {
                    QXmlStreamAttributes streamAttributes = xml.attributes();
                    m_policies.setPasswordChangesNum(ViAuthorisationConversions::qStringToInt(streamAttributes.value("num").toString()));
                    m_policies.setPasswordChanges(ViAuthorisationConversions::qStringToBool(xml.readElementText()));
                }
                else if (xml.name() == "minLength")
                {
                    QXmlStreamAttributes streamAttributes = xml.attributes();
                    m_policies.setMinLengthNum(ViAuthorisationConversions::qStringToInt(streamAttributes.value("num").toString()));
                    m_policies.setMinLength(ViAuthorisationConversions::qStringToBool(xml.readElementText()));
                }
                else if (xml.name() == "changeAtFirstLogin")
                {
                    m_policies.setChangeAtFirstLogin(ViAuthorisationConversions::qStringToBool(xml.readElementText()));
                }
                else if (xml.name() == "number")
                {
                    m_policies.setNumber(ViAuthorisationConversions::qStringToBool(xml.readElementText()));
                }
                else if (xml.name() == "specialCharacter")
                {
                    m_policies.setSpecialCharacter(ViAuthorisationConversions::qStringToBool(xml.readElementText()));
                }
                else if (xml.name() == "upperLowerCase")
                {
                    m_policies.setUpperLowerCase(ViAuthorisationConversions::qStringToBool(xml.readElementText()));
                }
                else
                {
                    xml.skipCurrentElement();
                }
            }

            m_policies.setLastChange(lastChange);
        }
        else if (xml.name() == "languages")
        {
            QXmlStreamAttributes streamAttributes = xml.attributes();
            m_languagesLastChange = ViAuthorisationConversions::qStringToQDateTime(streamAttributes.value("lastChange").toString());

            while (xml.readNextStartElement())
            {
                if (xml.name() == "language")
                {
                    m_languages.append(xml.readElementText());
                }
                else
                {
                    xml.skipCurrentElement();
                }
            }
        }
        else if (xml.name() == "domains")
        {
            QXmlStreamAttributes streamAttributes = xml.attributes();
            m_domainsLastChange = ViAuthorisationConversions::qStringToQDateTime(streamAttributes.value("lastChange").toString());

            while (xml.readNextStartElement())
            {
                if (xml.name() == "domain")
                {
                    QXmlStreamAttributes streamAttributesDomain = xml.attributes();
                    QString domain = xml.readElementText();

                    if (ViAuthorisationConversions::qStringToBool(streamAttributesDomain.value("default").toString()))
                    {
                        m_defaultDomain = domain;
                    }

                    m_domains.append(domain);
                }
                else
                {
                    xml.skipCurrentElement();
                }
            }
        }
        else
        {
            xml.skipCurrentElement();
        }
    }
}*/
}

bool Settings::toXml()
{
    QFile file(m_fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.setAutoFormattingIndent(2);
    xml.writeStartDocument();

    xml.writeStartElement("TuKiBazarSettings");

    xml.writeTextElement("Pc", QString("%1").arg(getPc()));
    xml.writeTextElement("SellerMin", QString("%1").arg(getSellerMin()));
    xml.writeTextElement("SellerMax", QString("%1").arg(getSellerMax()));
    xml.writeTextElement("ProductMin", QString("%1").arg(getProductMin()));
    xml.writeTextElement("ProductMax", QString("%1").arg(getProductMax()));

    xml.writeEndElement(); // TuKiBazarSettings
    xml.writeEndDocument();

    file.close();

    return true;


    /*xml.writeStartElement("ViAuthorisationMain");
    xml.writeAttribute("lastChange", ViAuthorisationConversions::qDateTimeToQString(m_lastChangeMain));
    xml.writeAttribute("version", ViAuthorisationConversions::intToQString(1));
    xml.writeTextElement("IP-Address", m_ip);
    xml.writeTextElement("AllowFallBackToLocalAuthentication", ViAuthorisationConversions::boolToQString(m_allowFallBackToLocalAuthentication));
    xml.writeTextElement("UserConfigFilePath", m_userConfigurationFilePath);
    xml.writeTextElement("RoleConfigFilePath", m_roleConfigurationFilePath);
    xml.writeTextElement("ComputerGroupConfigFilePath", m_computerGroupConfigurationFilePath);

    xml.writeStartElement("policies");
    xml.writeAttribute("lastChange", ViAuthorisationConversions::qDateTimeToQString(m_policies.getLastChange()));

    xml.writeStartElement("history");
    xml.writeAttribute("num", ViAuthorisationConversions::intToQString(m_policies.getPasswordHistoryNum()));
    xml.writeCharacters(ViAuthorisationConversions::boolToQString(m_policies.getPasswordHistory()));
    xml.writeEndElement(); // history

    xml.writeStartElement("blockAfterFail");
    xml.writeAttribute("num", ViAuthorisationConversions::intToQString(m_policies.getBlockAfterFailNum()));
    xml.writeCharacters(ViAuthorisationConversions::boolToQString(m_policies.getBlockAfterFail()));
    xml.writeEndElement(); // blockAfterFail

    xml.writeStartElement("automaticLogout");
    xml.writeAttribute("num", ViAuthorisationConversions::intToQString(m_policies.getAutomaticLogoutNum()));
    xml.writeCharacters(ViAuthorisationConversions::boolToQString(m_policies.getAutomaticLogout()));
    xml.writeEndElement(); // automaticLogout

    xml.writeStartElement("passwordChanges");
    xml.writeAttribute("num", ViAuthorisationConversions::intToQString(m_policies.getPasswordChangesNum()));
    xml.writeCharacters(ViAuthorisationConversions::boolToQString(m_policies.getPasswordChanges()));
    xml.writeEndElement(); // passwordChanges

    xml.writeStartElement("minLength");
    xml.writeAttribute("num", ViAuthorisationConversions::intToQString(m_policies.getMinLengthNum()));
    xml.writeCharacters(ViAuthorisationConversions::boolToQString(m_policies.getMinLength()));
    xml.writeEndElement(); // minLength

    xml.writeTextElement("changeAtFirstLogin", ViAuthorisationConversions::boolToQString(m_policies.getChangeAtFirstLogin()));
    xml.writeTextElement("number",             ViAuthorisationConversions::boolToQString(m_policies.getNumber()));
    xml.writeTextElement("specialCharacter",   ViAuthorisationConversions::boolToQString(m_policies.getSpecialCharacter()));
    xml.writeTextElement("upperLowerCase",     ViAuthorisationConversions::boolToQString(m_policies.getUpperLowerCase()));

    xml.writeEndElement(); // policies

    xml.writeStartElement("languages");
    xml.writeAttribute("lastChange", ViAuthorisationConversions::qDateTimeToQString(m_languagesLastChange));

    for (int i = 0; i < m_languages.length(); i++)
    {
        xml.writeTextElement("language", m_languages[i]);
    }

    xml.writeEndElement(); // languages

    xml.writeStartElement("domains");
    xml.writeAttribute("lastChange", ViAuthorisationConversions::qDateTimeToQString(m_domainsLastChange));

    for (int i = 0; i < m_domains.length(); i++)
    {
        xml.writeStartElement("domain");

        if (m_domains[i] == m_defaultDomain)
        {
            xml.writeAttribute("default", ViAuthorisationConversions::boolToQString(true));
        }

        xml.writeCharacters(m_domains[i]);
        xml.writeEndElement(); // domain
    }

    xml.writeEndElement(); // domains

    xml.writeEndElement(); // ViAuthorisation
    xml.writeEndElement(); // ViParameter
    xml.writeEndDocument();

    file.close();*/
}

void Settings::on_pushButtonOk_clicked()
{
    if (ui->spinBoxSellerMax->value() < ui->spinBoxSellerMin->value())
    {
        QMessageBox mb;
        mb.setText(tr("Die maximale Verkäufernummer darf nicht kleiner als die minimale Verkäufernummer sein!"));
        mb.exec();
        return;
    }

    if (ui->spinBoxProductMax->value() < ui->spinBoxProductMin->value())
    {
        QMessageBox mb;
        mb.setText(tr("Die maximale Produktnummer darf nicht kleiner als die minimale Produktnummer sein!"));
        mb.exec();
        return;
    }

    toXml();

    this->accept();
}
