#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <vector>

#include <QDebug>
#include <QMutex>
#include <QMutexLocker>

// ToDo Protection Mutex

template<typename T>
class RingBuffer
{
public:
  RingBuffer(int size);

  void write(T value);
  bool read(T& value);

  void printValues();

private:
  QMutex m_mutex;
  int m_size;
  int m_writeIndex;
  int m_readIndex;
  int m_overwrittenValues;
  std::vector<T> m_values;
};


template<typename T>
RingBuffer<T>::RingBuffer(int size) :
  m_size(size),
  m_writeIndex(0),
  m_readIndex(0),
  m_overwrittenValues(0)
{
  m_values.resize(size);
}

template<typename T>
void RingBuffer<T>::write(T value)
{
  QMutexLocker locker(&m_mutex);

  int newWriteIndex = (m_writeIndex + 1) % m_size;

  if (newWriteIndex == m_readIndex)
  {
    m_overwrittenValues++;
    m_readIndex = (m_readIndex + 1) % m_size;
  }

  m_values[m_writeIndex] = value;
  m_writeIndex = newWriteIndex;
}

template<typename T>
bool RingBuffer<T>::read(T& value)
{
  QMutexLocker locker(&m_mutex);
  // TODO change interface - read may be not possible - bool as return value and call by reference

  // TODO check writeIndex

  value = m_values[m_readIndex];
  m_readIndex = (m_readIndex + 1) % m_size;
  return true;
}

template<typename T>
void RingBuffer<T>::printValues()
{
  for (auto it = m_values.begin(); it != m_values.end(); ++it)
  {
    qDebug() << *it;
  }
}

#endif // RINGBUFFER_H
