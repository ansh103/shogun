/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2008 Soeren Sonnenburg
 * Written (W) 1999-2008 Gunnar Raetsch
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */


#ifndef _CFEATURES__H__
#define _CFEATURES__H__

#include "lib/common.h"
#include "base/SGObject.h"

enum EFeatureType
{
	F_UNKNOWN = 0,
	F_CHAR = 10,
	F_BYTE = 20,
	F_SHORT = 30,
	F_WORD = 40,
	F_INT = 50,
	F_UINT = 60,
	F_LONG = 70,
	F_ULONG = 80,
	F_SHORTREAL = 90,
	F_DREAL = 100,
	F_LONGREAL = 110,
	F_ANY = 1000
};

enum EFeatureClass
{
	C_UNKNOWN = 0,
	C_SIMPLE = 10,
	C_SPARSE = 20,
	C_STRING = 30,
	C_COMBINED = 40,
	C_MINDYGRAM = 50,
	C_ANY = 1000
};


#include "preproc/PreProc.h"
class CPreProc;
class CFeatures;


/** The class Features is the base class of all feature objects. It can be
 * understood as a dense real valued feature matrix (with e.g. columns as
 * single feature vectors), a set of strings, graphs or any other arbitrary
 * collection of objects. As a result this class is kept very general and
 * implements only very weak interfaces to
 *
 * - duplicate the Feature object
 * - obtain the feature type (like DREALs, SHORT ...)
 * - obtain the feature class (like Simple dense matrices, sparse or strings)
 * - obtain the number of feature "vectors"
 *
 *   In addition it provides helpers to check e.g. for compability of feature objects.
 *
 *   Currently there are 3 general feature classes, which are CSimpleFeatures
 *   (dense matrices), CSparseFeatures (sparse matrices), CStringFeatures (a
 *   set of strings) from which all the specific features like CRealFeatures
 *   (dense real valued feature matrices) are derived.
 */
class CFeatures : public CSGObject
{
	public:
		/** constructor
		 *
		 * @param size cache size
		 */
		CFeatures(int32_t size);

		/** copy constructor */
		CFeatures(const CFeatures& orig);

		/** constructor
		 *
		 * @param fname filename to load features from
		 */
		CFeatures(char* fname);

		/** duplicate feature object
		 *
		 * abstract base method
		 *
		 * @return feature object
		 */
		virtual CFeatures* duplicate() const=0 ;

		virtual ~CFeatures();

		/** get feature type
		 *
		 * abstract base method
		 *
		 * @return templated feature type
		 */
		virtual EFeatureType get_feature_type()=0;

		/** get feature class
		 *
		 * abstract base method
		 *
		 * @return feature class like STRING, SIMPLE, SPARSE...
		 */
		virtual EFeatureClass get_feature_class()=0;

		/** add preprocessor
		 *
		 * @param p preprocessor to set
		 * @return something inty
		 */
		virtual int32_t add_preproc(CPreProc* p);

		/** delete preprocessor from list
		 * caller has to clean up returned preproc
		 *
		 * @param num index of preprocessor in list
		 */
		virtual CPreProc* del_preproc(int32_t num);

		/** get specified preprocessor
		 *
		 * @param num index of preprocessor in list
		 */
		CPreProc* get_preproc(int32_t num);

		/** set applied flag for preprocessor
		 *
		 * @param num index of preprocessor in list
		 */
		inline void set_preprocessed(int32_t num) { preprocessed[num]=true; }

		/** get whether specified preprocessor was already applied
		 *
		 * @param num index of preprocessor in list
		 */
		inline bool is_preprocessed(int32_t num) { return preprocessed[num]; }

		/** get the number of applied preprocs
		 *
		 * @return number of applied preprocessors
		 */
		int32_t get_num_preprocessed();

		/** get number of preprocessors
		 *
		 * @return number of preprocessors
		 */
		inline int32_t get_num_preproc() { return num_preproc; }

		/** clears all preprocs */
		void clean_preprocs();

		/** get cache size
		 *
		 * @return cache size
		 */
		inline int32_t get_cache_size() { return cache_size; };

		/** get number of examples/vectors
		 *
		 * abstract base method
		 *
		 * @return number of examples/vectors
		 */
		virtual int32_t get_num_vectors()=0 ;

		/** in case there is a feature matrix allow for reshaping
		 *
		 * NOT IMPLEMENTED!
		 *
		 * @param num_features new number of features
		 * @param num_vectors new number of vectors
		 * @return if reshaping was succesful
		 */
		virtual bool reshape(int32_t num_features, int32_t num_vectors) { return false; }

		/** get memory footprint of one feature
		 *
		 * abstrace base method
		 *
		 * @return memory footprint of one feature
		 */
		virtual int32_t get_size()=0;

		/** list feature object */
		void list_feature_obj();

		/** load features from file
		 *
		 * @param fname filename to load from
		 * @return if loading was successful
		 */
		virtual bool load(char* fname);

		/** save features to file
		 *
		 * @param fname filename to save to
		 * @return if saving was successful
		 */
		virtual bool save(char* fname);

		/** check feature compatibility
		 *
		 * @param f features to check for compatibility
		 * @return if features are compatible
		 */
		bool check_feature_compatibility(CFeatures* f);

	private:
		/// size of cache in MB
		int32_t cache_size;

		/// list of preprocessors
		CPreProc** preproc;

		/// number of preprocs in list
		int32_t num_preproc;

		/// i'th entry is true if features were already preprocessed with preproc i
		bool* preprocessed;
};
#endif
