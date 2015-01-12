#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics
{
public:
  Statistics();

  int m_countOfSales;
  int m_countOfSoldArticles;
  int m_countOfAllArticles;

  double m_volumeOfSale;
  double m_deduction;
  double m_deductionPercentage;
  double m_articlesPerSale;
  double m_percentageOfSoldArticles;
};

#endif // STATISTICS_H
