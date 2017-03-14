//
// Created by AJ Pryor on 3/5/17.
//

#include "meta.h"
#include "params.h"
#include "ArrayND.h"
#include "configure.h"
#include "Multislice.h"
#include "PRISM01.h"
#include "PRISM02.h"
#include <algorithm>


namespace PRISM{
	int Multislice_entry(Metadata<PRISM_FLOAT_PRECISION>& meta){

		using vec_d = std::vector<PRISM_FLOAT_PRECISION>;
		using Array3D = ArrayND<3, vec_d>;
		using Array2D = ArrayND<2, vec_d>;
		using Array1D = ArrayND<1, vec_d>;
		using Array1D_dims = ArrayND<1, std::vector<size_t> >;

		cout << MESSAGE << endl;
		Parameters<PRISM_FLOAT_PRECISION> prism_pars(meta);
		std::cout<<"Dummy code for Multislice entrypoint" << std::endl;
		PRISM01(prism_pars);
		prism_pars.pot.toMRC_f("DEBUG.mrc");
		cout << "entering multislice\n";
		Multislice(prism_pars);
//		PRISM02(prism_pars);
//		PRISM03(prism_pars);

//
		cout << "prism_pars.stack.at(0,0,0) = " << prism_pars.stack.at(0,0,0) << endl;
		float t = 0;
		for (auto i : prism_pars.stack) t += i;
		cout << "stack sum = " << t << endl;

		t = 0;
		for (auto i = 0; i < prism_pars.stack.get_dimi() ; ++i) t += prism_pars.stack.at(0,0,i);
		cout << "stack sum 0,0,:= " << t << endl;

//		size_t lower = 15;
//		size_t upper = 16;
		size_t lower = 13;
		size_t upper = 18;
		Array2D prism_image;
		cout << "prism_pars.stack.get_diml() = " << prism_pars.stack.get_diml() << endl;
		cout << "prism_pars.stack.get_dimk() = " << prism_pars.stack.get_dimk() << endl;
		cout << "prism_pars.stack.get_dimj() = " << prism_pars.stack.get_dimj() << endl;
//		prism_image = zeros_ND<2, PRISM_FLOAT_PRECISION>({{25,25}});
		prism_image = zeros_ND<2, PRISM_FLOAT_PRECISION>({{prism_pars.stack.get_diml(), prism_pars.stack.get_dimk()}});
		for (auto y = 0; y < prism_pars.stack.get_diml(); ++y){
			for (auto x = 0; x < prism_pars.stack.get_dimk(); ++x){
				for (auto b = lower; b < upper; ++b){
					prism_image.at(y,x) += prism_pars.stack.at(y,x,b,0);
				}
			}
		}

		prism_image.toMRC_f(prism_pars.meta.filename_output.c_str());





		Array3D debug = zeros_ND<3, PRISM_FLOAT_PRECISION>({{prism_pars.stack.get_diml(), prism_pars.stack.get_dimk(),prism_pars.stack.get_dimj() }});
		auto b = debug.begin();
		for (auto &i:prism_pars.stack)*b++ = i;
		debug.toMRC_f("stack.mrc");



		std::cout << "Calculation complete.\n" << std::endl;
		return 0;
	}

}