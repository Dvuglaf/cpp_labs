#pragma once

#include <QImage>

/**
 * ��������� ����������� ����.
 */
class Settings final {
  
    QImage* _background; /**< ������� �����������. */
    QImage* _fruit; /**< ����������� ������. */
    qint32 _difficulty = 100; /**< ��������� ���� � (��) -  �������� ��������� ����� ������������ �������. */

public:

    static const qint32 MIN_DIFFICULTY = 140; /**< ���������� ��������� �������� ��������� ����� ������������ �������. */
    static const qint32 MAX_DIFFICULTY = 65; /**< ����������� ��������� �������� ��������� ����� ������������ �������. */
 

    /**
     * ����������� �� ���������.
     */
    Settings();
    
    /**
     * ����������� ����������� �����������.
     */
    Settings(const Settings&) = delete;

    /**
     * ����������� �������� ������������ ������������.
     */
    Settings& operator=(const Settings&) = delete;

    /**
     * ���������� ����������� �������� ����������� � ���� ���������.
     *
     * @return ��������� �� ������ �������� �����������.
     */
    QImage* background() const;

    /**
    * ���������� ����������� ������ � ���� ���������.
    *
    * @return ��������� �� ������ ����������� ������.
    */
    QImage* fruit() const;

    /**
    * ������������� ������� �����������.
    *
    * @param image O��e�� �������� �����������.
    */
    void setBackground(QImage* image);

    /**
     * ������������� ����������� ������.
     *
     * @param image O��e�� ����������� ������.
     */
    void setFruit(QImage* image);

    /**
    * ���������� ������� �������� ��������� ����.
    *
    * @return �������� ��������� ����� ������������ �������.
    */
    qint32 difficulty() const;

    /**
    * ������������� �������� ��������� ����.
    *
    * @param value �������� ��������� ����� ������������ �������.
    */
    void setDifficulty(qint32 value);


};