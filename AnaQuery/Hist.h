#pragma once

#include <memory>
#include <string>
#include <vector>

#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <ROOT/RVec.hxx>

#include <queryosity.hpp>

namespace AnaQ {

template <int Dim, typename Prec> class Hist;

template <typename Prec>
class Hist<1, Prec>
    : public queryosity::query::definition<std::shared_ptr<TH1>(Prec)> {

public:
  Hist(const std::string &, unsigned int, double, double);
  Hist(const std::string &, const std::vector<double> &);
  virtual ~Hist() = default;

  virtual void fill(queryosity::column::observable<Prec>,
                    double) final override;
  virtual std::shared_ptr<TH1> result() const final override;
  virtual std::shared_ptr<TH1>
  merge(std::vector<std::shared_ptr<TH1>> const &results) const final override;

protected:
  // histogram
  std::shared_ptr<TH1> m_hist; //!
};

template <typename Prec>
class Hist<2, Prec>
    : public queryosity::query::definition<std::shared_ptr<TH2>(Prec, Prec)> {

public:
  Hist(const std::string &, const std::vector<double> &,
       const std::vector<double> &);
  virtual ~Hist() = default;

  virtual void fill(queryosity::column::observable<Prec>,
                    queryosity::column::observable<Prec>,
                    double) final override;
  virtual std::shared_ptr<TH2> result() const final override;
  virtual std::shared_ptr<TH2>
  merge(std::vector<std::shared_ptr<TH2>> const &results) const final override;

protected:
  std::shared_ptr<TH2> m_hist; //!
};

template <typename Prec>
class Hist<3, Prec> : public queryosity::query::definition<std::shared_ptr<TH3>(
                          Prec, Prec, Prec)> {

public:
  Hist(const std::string &, const std::vector<double> &,
       const std::vector<double> &, const std::vector<double> &);
  virtual ~Hist() = default;

  virtual void fill(queryosity::column::observable<Prec>,
                    queryosity::column::observable<Prec>,
                    queryosity::column::observable<Prec>,
                    double) final override;
  virtual std::shared_ptr<TH3> result() const final override;
  virtual std::shared_ptr<TH3>
  merge(std::vector<std::shared_ptr<TH3>> const &results) const final override;

protected:
  std::shared_ptr<TH3> m_hist; //!
};

template <typename Prec>
class Hist<1, ROOT::RVec<Prec>>
    : public queryosity::query::definition<std::shared_ptr<TH1>(
          ROOT::RVec<Prec>)> {

public:
  Hist(const std::string &name, unsigned int nbins, double min, double xmax);
  Hist(const std::string &name, const std::vector<double> &xbins);
  virtual ~Hist() = default;

  virtual void fill(queryosity::column::observable<ROOT::RVec<Prec>>,
                    double) final override;
  virtual std::shared_ptr<TH1> result() const final override;
  virtual std::shared_ptr<TH1>
  merge(std::vector<std::shared_ptr<TH1>> const &results) const final override;

protected:
  // histogram
  std::shared_ptr<TH1> m_hist; //!
};

template <typename Prec>
class Hist<2, ROOT::RVec<Prec>>
    : public queryosity::query::definition<std::shared_ptr<TH2>(
          ROOT::RVec<Prec>, ROOT::RVec<Prec>)> {

public:
  Hist(const std::string &, const std::vector<double> &,
       const std::vector<double> &);
  virtual ~Hist() = default;

  virtual void fill(queryosity::column::observable<ROOT::RVec<Prec>>,
                    queryosity::column::observable<ROOT::RVec<Prec>>,
                    double) final override;
  virtual std::shared_ptr<TH2> result() const final override;
  virtual std::shared_ptr<TH2>
  merge(std::vector<std::shared_ptr<TH2>> const &results) const final override;

protected:
  // histogram
  std::shared_ptr<TH2> m_hist; //!
};

template <typename Prec>
class Hist<3, ROOT::RVec<Prec>>
    : public queryosity::query::definition<std::shared_ptr<TH3>(
          ROOT::RVec<Prec>, ROOT::RVec<Prec>, ROOT::RVec<Prec>)> {

public:
  Hist(const std::string &, const std::vector<double> &,
       const std::vector<double> &, const std::vector<double> &);
  virtual ~Hist() = default;

  virtual void fill(queryosity::column::observable<ROOT::RVec<Prec>>,
                    queryosity::column::observable<ROOT::RVec<Prec>>,
                    queryosity::column::observable<ROOT::RVec<Prec>>,
                    double) final override;
  virtual std::shared_ptr<TH3> result() const final override;
  virtual std::shared_ptr<TH3>
  merge(std::vector<std::shared_ptr<TH3>> const &results) const final override;

protected:
  // histogram
  std::shared_ptr<TH3> m_hist; //!
};

} // namespace AnaQ

#include "AnaQuery/HistHelpers.h"

template <typename Prec>
AnaQ::Hist<1, Prec>::Hist(const std::string &name, unsigned int nbins,
                          double xmin, double xmax)
    : queryosity::query::definition<std::shared_ptr<TH1>(Prec)>() {
  m_hist = HistHelpers::makeHist<1, Prec>(nbins, xmin, xmax);
  m_hist->SetName(name.c_str());
}

template <typename Prec>
AnaQ::Hist<1, Prec>::Hist(const std::string &name,
                          const std::vector<double> &xbins) {
  m_hist = HistHelpers::makeHist<1, Prec>(xbins);
  m_hist->SetName(name.c_str());
}

template <typename Prec>
void AnaQ::Hist<1, Prec>::fill(queryosity::column::observable<Prec> x,
                               double w) {
  m_hist->Fill(x.value(), w);
}

template <typename Prec>
std::shared_ptr<TH1> AnaQ::Hist<1, Prec>::result() const {
  return m_hist;
}

template <typename Prec>
std::shared_ptr<TH1> AnaQ::Hist<1, Prec>::merge(
    std::vector<std::shared_ptr<TH1>> const &results) const {
  auto merged_result =
      std::shared_ptr<TH1>(static_cast<TH1 *>(results[0]->Clone()));
  for (size_t islot = 1; islot < results.size(); ++islot) {
    merged_result->Add(results[islot].get());
  }
  return merged_result;
}

template <typename Prec>
AnaQ::Hist<2, Prec>::Hist(const std::string &name,
                          const std::vector<double> &xbins,
                          const std::vector<double> &ybins) {
  m_hist = std::static_pointer_cast<TH2>(
      HistHelpers::makeHist<2, Prec>(xbins, ybins));
  m_hist->SetName(name.c_str());
}

template <typename Prec>
void AnaQ::Hist<2, Prec>::fill(queryosity::column::observable<Prec> x,
                               queryosity::column::observable<Prec> y,
                               double w) {
  m_hist->Fill(x.value(), y.value(), w);
}

template <typename Prec>
std::shared_ptr<TH2> AnaQ::Hist<2, Prec>::merge(
    std::vector<std::shared_ptr<TH2>> const &results) const {
  auto merged_result =
      std::shared_ptr<TH2>(static_cast<TH2 *>(results[0]->Clone()));
  for (size_t islot = 1; islot < results.size(); ++islot) {
    merged_result->Add(results[islot].get());
  }
  return merged_result;
}

template <typename Prec>
std::shared_ptr<TH2> AnaQ::Hist<2, Prec>::result() const {
  return m_hist;
}

template <typename Prec>
AnaQ::Hist<3, Prec>::Hist(const std::string &name,
                          const std::vector<double> &xbins,
                          const std::vector<double> &ybins,
                          const std::vector<double> &zbins)
    : queryosity::query::definition<std::shared_ptr<TH3>(Prec, Prec, Prec)>() {
  m_hist = std::static_pointer_cast<TH3>(
      HistHelpers::makeHist<3, Prec>(xbins, ybins, zbins));
  m_hist->SetName(name.c_str());
}

template <typename Prec>
void AnaQ::Hist<3, Prec>::fill(queryosity::column::observable<Prec> x,
                               queryosity::column::observable<Prec> y,
                               queryosity::column::observable<Prec> z,
                               double w) {
  m_hist->Fill(x.value(), y.value(), z.value(), w);
}

template <typename Prec>
std::shared_ptr<TH3> AnaQ::Hist<3, Prec>::merge(
    std::vector<std::shared_ptr<TH3>> const &results) const {
  auto merged_result =
      std::shared_ptr<TH3>(static_cast<TH3 *>(results[0]->Clone()));
  for (size_t islot = 1; islot < results.size(); ++islot) {
    merged_result->Add(results[islot].get());
  }
  return merged_result;
}

template <typename Prec>
std::shared_ptr<TH3> AnaQ::Hist<3, Prec>::result() const {
  return m_hist;
}

// vector<T>

template <typename Prec>
AnaQ::Hist<1, ROOT::RVec<Prec>>::Hist(const std::string &name,
                                      unsigned int nbins, double xmin,
                                      double xmax) {
  m_hist = HistHelpers::makeHist<1, Prec>(nbins, xmin, xmax);
  m_hist->SetName(name.c_str());
}

template <typename Prec>
AnaQ::Hist<1, ROOT::RVec<Prec>>::Hist(const std::string &name,
                                      const std::vector<double> &xbins) {
  m_hist = HistHelpers::makeHist<1, Prec>(xbins);
  m_hist->SetName(name.c_str());
}

template <typename Prec>
void AnaQ::Hist<1, ROOT::RVec<Prec>>::fill(
    queryosity::column::observable<ROOT::RVec<Prec>> xs, double w) {
  for (size_t ix = 0; ix < xs->size(); ++ix) {
    m_hist->Fill(xs.value()[ix], w);
  }
}

template <typename Prec>
std::shared_ptr<TH1> AnaQ::Hist<1, ROOT::RVec<Prec>>::merge(
    std::vector<std::shared_ptr<TH1>> const &results) const {
  auto merged_result =
      std::shared_ptr<TH1>(static_cast<TH1 *>(results[0]->Clone()));
  for (size_t islot = 1; islot < results.size(); ++islot) {
    merged_result->Add(results[islot].get());
  }
  return merged_result;
}

template <typename Prec>
std::shared_ptr<TH1> AnaQ::Hist<1, ROOT::RVec<Prec>>::result() const {
  return m_hist;
}

template <typename Prec>
AnaQ::Hist<2, ROOT::RVec<Prec>>::Hist(const std::string &name,
                                      const std::vector<double> &xbins,
                                      const std::vector<double> &ybins) {
  m_hist = std::static_pointer_cast<TH2>(
      HistHelpers::makeHist<2, Prec>(xbins, ybins));
  m_hist->SetName(name.c_str());
}

template <typename Prec>
void AnaQ::Hist<2, ROOT::RVec<Prec>>::fill(
    queryosity::column::observable<ROOT::RVec<Prec>> xs,
    queryosity::column::observable<ROOT::RVec<Prec>> ys, double w) {
  if (xs->size() != ys->size()) {
    throw std::runtime_error("x- and y-arrays do not share the same size");
  }
  for (size_t ix = 0; ix < xs->size(); ++ix) {
    m_hist->Fill(xs.value()[ix], ys.value()[ix], w);
  }
}

template <typename Prec>
std::shared_ptr<TH2> AnaQ::Hist<2, ROOT::RVec<Prec>>::merge(
    std::vector<std::shared_ptr<TH2>> const &results) const {
  auto merged_result =
      std::shared_ptr<TH2>(static_cast<TH2 *>(results[0]->Clone()));
  for (size_t islot = 1; islot < results.size(); ++islot) {
    merged_result->Add(results[islot].get());
  }
  return merged_result;
}

template <typename Prec>
std::shared_ptr<TH2> AnaQ::Hist<2, ROOT::RVec<Prec>>::result() const {
  return m_hist;
}

template <typename Prec>
AnaQ::Hist<3, ROOT::RVec<Prec>>::Hist(const std::string &name,
                                      const std::vector<double> &xbins,
                                      const std::vector<double> &ybins,
                                      const std::vector<double> &zbins) {
  m_hist = std::static_pointer_cast<TH3>(
      HistHelpers::makeHist<3, Prec>(xbins, ybins, zbins));
  m_hist->SetName(name.c_str());
}

template <typename Prec>
void AnaQ::Hist<3, ROOT::RVec<Prec>>::fill(
    queryosity::column::observable<ROOT::RVec<Prec>> xs,
    queryosity::column::observable<ROOT::RVec<Prec>> ys,
    queryosity::column::observable<ROOT::RVec<Prec>> zs, double w) {
  if (xs->size() != ys->size()) {
    throw std::runtime_error("x- and y-arrays do not share the same size");
  }
  if (xs->size() != zs->size()) {
    throw std::runtime_error("x- and z-arrays do not share the same size");
  }
  for (size_t ix = 0; ix < xs->size(); ++ix) {
    m_hist->Fill(xs.value()[ix], ys.value()[ix], zs.value()[ix], w);
  }
}

template <typename Prec>
std::shared_ptr<TH3> AnaQ::Hist<3, ROOT::RVec<Prec>>::merge(
    std::vector<std::shared_ptr<TH3>> const &results) const {
  auto merged_result =
      std::shared_ptr<TH3>(static_cast<TH3 *>(results[0]->Clone()));
  for (size_t islot = 1; islot < results.size(); ++islot) {
    merged_result->Add(results[islot].get());
  }
  return merged_result;
}

template <typename Prec>
std::shared_ptr<TH3> AnaQ::Hist<3, ROOT::RVec<Prec>>::result() const {
  return m_hist;
}

template class AnaQ::Hist<1, float>;
template class AnaQ::Hist<2, float>;
template class AnaQ::Hist<3, float>;
template class AnaQ::Hist<1, ROOT::RVec<float>>;
template class AnaQ::Hist<2, ROOT::RVec<float>>;
template class AnaQ::Hist<3, ROOT::RVec<float>>;