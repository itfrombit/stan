#ifndef __STAN__DIFF__REV__LOG_SUM_EXP_HPP__
#define __STAN__DIFF__REV__LOG_SUM_EXP_HPP__

#include <stan/diff/rev/var.hpp>
#include <stan/diff/rev/calculate_chain.hpp>
#include <stan/diff/rev/scalar/op/vv_vari.hpp>
#include <stan/diff/rev/scalar/op/vd_vari.hpp>
#include <stan/diff/rev/scalar/op/dv_vari.hpp>
#include <stan/diff/rev/scalar/op/vector_vari.hpp>
#include <stan/diff/rev/scalar/operator_greater_than.hpp>
#include <stan/diff/rev/scalar/operator_not_equal.hpp>
#include <stan/math/scalar/log_sum_exp.hpp>

namespace stan {
  namespace diff {

    namespace {
      double log_sum_exp_as_double(const std::vector<var>& x) {
        using std::numeric_limits;
        using std::exp;
        using std::log;
        double max = -numeric_limits<double>::infinity();
        for (size_t i = 0; i < x.size(); ++i) 
          if (x[i] > max) 
            max = x[i].val();
        double sum = 0.0;
        for (size_t i = 0; i < x.size(); ++i) 
          if (x[i] != -numeric_limits<double>::infinity()) 
            sum += exp(x[i].val() - max);
        return max + log(sum);
      }

      class log_sum_exp_vector_vari : public op_vector_vari {
      public:
        log_sum_exp_vector_vari(const std::vector<var>& x) :
          op_vector_vari(log_sum_exp_as_double(x), x) {
        }
        void chain() {
          for (size_t i = 0; i < size_; ++i) {
            vis_[i]->adj_ += adj_ * calculate_chain(vis_[i]->val_, val_);
          }
        }
      };
    }

    /**
     * Returns the log sum of exponentials.
     */
    inline var log_sum_exp(const std::vector<var>& x) {
      return var(new log_sum_exp_vector_vari(x));
    }

  }
}
#endif
