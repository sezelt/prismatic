#ifndef PRISM_MULTISLICE_CUH
#define PRISM_MULTISLICE_CUH
#include "params.h"
#include "configure.h"
#include <complex>
namespace PRISM {
    void buildMultisliceOutput_gpu(Parameters <PRISM_FLOAT_PRECISION> &pars,
                                   Array3D <std::complex<PRISM_FLOAT_PRECISION>> &trans,
                                   Array2D <std::complex<PRISM_FLOAT_PRECISION>> &PsiProbeInit,
                                   Array2D <PRISM_FLOAT_PRECISION> &alphaInd);
	void formatOutput_gpu_integrate(Parameters<PRISM_FLOAT_PRECISION>& pars,
                                    PRISM_FLOAT_PRECISION * psi,
                                    const PRISM_FLOAT_PRECISION * alphaInd,
                                    PRISM_FLOAT_PRECISION * integratedOutput,
                                    const size_t& ay,
                                    const size_t& ax,
	                                const size_t&,
	                                const size_t&);
}
#endif //PRISM_MULTISLICE_CUH
