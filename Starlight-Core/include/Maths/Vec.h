/*Copyright 2015 Sean Mooney

Licensed under the Apache License,Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/
#pragma once
#include "STARLIGHT_CORE\Shared.h"
// useing https://github.com/d-frey/operators.git for operators.
#include <df\operators.hpp>
#include <iostream>
#include <array>
namespace starlight{
	namespace core{
		namespace maths{
			template<typename T>
			struct  VecBase : df::commutative_addable<T>,
				df::commutative_multipliable<T>,
				df::dividable<T>,df::subtractable<T>,
				df::commutative_addable<T,STARLIGHT_PRECISSION>,
				df::commutative_multipliable<T,STARLIGHT_PRECISSION>,
				df::dividable<T,STARLIGHT_PRECISSION>,
				df::subtractable<T,STARLIGHT_PRECISSION>,
				df::totally_ordered<T>{

				T& operator+=(const STARLIGHT_PRECISSION rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					for(STARLIGHT_PRECISSION& x : reference.data_array){
						x+=rhs;
					}
					return reference;
				}

				T& operator-=(const STARLIGHT_PRECISSION rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					for(STARLIGHT_PRECISSION& x : reference.data_array){
						 x-=rhs;
					}
					return reference;
				}

				T& operator*=(const STARLIGHT_PRECISSION rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					for(STARLIGHT_PRECISSION& x : reference.data_array){
						 x*=rhs;
					}
					return reference;
				}

				T& operator/=(const STARLIGHT_PRECISSION rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					for(STARLIGHT_PRECISSION& x : reference.data_array){
						 x/=rhs;
					}
					return reference;
				}

				T& operator+=(const T& rhs)noexcept{
					T& reference=static_cast<T&>(*this);
					for(unsigned int i=0; i<reference.data_array.size();i++){
						reference.data_array[i]=reference.data_array[i]+rhs.data_array[i];
					}
					return reference;
				}
				T& operator-=(const T& rhs)noexcept{
					T& reference=static_cast<T&>(*this);
					for(unsigned int i=0; i<reference.data_array.size();i++){
						reference.data_array[i]=reference.data_array[i]-rhs.data_array[i];
					}
					return reference;
				}
				T& operator*=(const T& rhs)noexcept{
					T& reference=static_cast<T&>(*this);
					for(unsigned int i=0; i<reference.data_array.size();i++){
						reference.data_array[i]=reference.data_array[i]*rhs.data_array[i];
					}
					return reference;
				}
				T& operator/=(const T& rhs)noexcept{
					T& reference=static_cast<T&>(*this);
					for(unsigned int i=0; i<reference.data_array.size();i++){
						reference.data_array[i]=reference.data_array[i]/rhs.data_array[i];
					}
					return reference;
				}
				bool operator==(const T& rhs)const noexcept{
					const T& reference(static_cast<const T&>(*this));
					bool result=true;
					for(unsigned int i=0; i<reference.data_array.size();i++){
						const STARLIGHT_PRECISSION& a=reference.data_array[i];
						const STARLIGHT_PRECISSION& b=rhs.data_array[i];
						result&=fabs(a-b)<std::numeric_limits<STARLIGHT_PRECISSION>::epsilon()*10;
					}
					return result;
				}
				bool operator<(const T& rhs)const noexcept{
					const T& reference(static_cast<const T&>(*this));
					bool result=false;
					for(unsigned int i=0; i<reference.data_array.size();i++){
						if(reference.data_array[i]==rhs.data_array[i]) continue;
						else return reference.data_array[i]<rhs.data_array[i];
					}
					return result;
				}

				friend std::ostream& operator<<(std::ostream& os,const T& rhs){
					STARLIGHT_OUTPUT_ARCHIVE archive(os);
					T& reference=const_cast<T&>(rhs);
					// dose not modify rhs
					reference.serialize(archive);
					return os;
				}

				friend std::istream& operator>>(std::istream& is,T& rhs){
					STARLIGHT_INPUT_ARCHIVE archive(is);
					rhs.serialize(archive);
					return is;
				}

				VecBase<T>(){
					T& reference(static_cast<T&>(*this));
					for(unsigned int i=0; i<reference.data_array.size();i++)
						reference.data_array[i]=0;
				}

			};

			struct STARLIGHTAPI Vec1 : public VecBase<Vec1>{
				union{
					std::array<STARLIGHT_PRECISSION,1> data_array;
					struct _Vec1{
						STARLIGHT_PRECISSION x;
						template <class Archive>
						void serialize(Archive & ar){
							ar(CEREAL_NVP(x));
						}
					} data;
				};
				Vec1()=default;
				Vec1(std::initializer_list<STARLIGHT_PRECISSION> l):VecBase<Vec1>(){
					data_array=reinterpret_cast<std::array< STARLIGHT_PRECISSION,1> const &>(*l.begin());
				}
				Vec1(const STARLIGHT_PRECISSION& x)
					:VecBase<Vec1>(){
					data.x=x;
				}
				template <class Archive>
				void serialize(Archive & ar){
					ar(cereal::make_nvp("Vec1",data));
				}

			};

			struct STARLIGHTAPI Vec2 : public VecBase<Vec2>{
				union{
					std::array<STARLIGHT_PRECISSION,2> data_array;
					struct _Vec2{
						STARLIGHT_PRECISSION x;
						STARLIGHT_PRECISSION y;
						template <class Archive>
						void serialize(Archive & ar){
							ar(CEREAL_NVP(x)
							   ,CEREAL_NVP(y));
						}
					} data;
				};
				Vec2()=default;
				Vec2(std::initializer_list<STARLIGHT_PRECISSION> l) :VecBase<Vec2>(){
						data_array=reinterpret_cast<std::array< STARLIGHT_PRECISSION,2> const &>(*l.begin());
				}
				Vec2(const STARLIGHT_PRECISSION& x,const STARLIGHT_PRECISSION& y)
					:VecBase<Vec2>(){
					data.x=x;
					data.y=y;
				}
				template <class Archive>
				void serialize(Archive & ar){
					ar(cereal::make_nvp("Vec2",data));
				}
			};

			struct STARLIGHTAPI Vec3 : public VecBase<Vec3>{
				union{
					std::array<STARLIGHT_PRECISSION,3> data_array;
					struct _Vec3{
						STARLIGHT_PRECISSION x;
						STARLIGHT_PRECISSION y;
						STARLIGHT_PRECISSION z;
						template <class Archive>
						void serialize(Archive & ar){
							ar( CEREAL_NVP(x)
							   ,CEREAL_NVP(y)
							   ,CEREAL_NVP(z));
						}
					} data;
				};
				Vec3()=default;
				Vec3(std::initializer_list<STARLIGHT_PRECISSION> l) :VecBase<Vec3>(){
					data_array=reinterpret_cast<std::array< STARLIGHT_PRECISSION,3> const &>(*l.begin());
				}
				Vec3(const STARLIGHT_PRECISSION& x,const STARLIGHT_PRECISSION& y,const STARLIGHT_PRECISSION& z)
					:VecBase<Vec3>(){
					data.x=x;
					data.y=y;
					data.z=z;
				}
				template <class Archive>
				void serialize(Archive & ar){
					ar(cereal::make_nvp("Vec3",data));
				}
			};

			struct STARLIGHTAPI _Vec4{
				STARLIGHT_PRECISSION x;
				STARLIGHT_PRECISSION y;
				STARLIGHT_PRECISSION z;
				STARLIGHT_PRECISSION w;
				template <class Archive>
				void serialize(Archive & ar){
					ar(CEREAL_NVP(x)
					   ,CEREAL_NVP(y)
					   ,CEREAL_NVP(z)
					   ,CEREAL_NVP(w));
				}
			};

			struct STARLIGHTAPI Vec4 : public VecBase<Vec4>{
				
				union{
					std::array<STARLIGHT_PRECISSION,4> data_array;
					_Vec4 data;
				};
				Vec4()=default;
				Vec4(const _Vec4& rhs) :VecBase<Vec4>(),data(rhs){};
				Vec4(std::initializer_list<STARLIGHT_PRECISSION> l) :VecBase<Vec4>(){
					data_array=reinterpret_cast<std::array< STARLIGHT_PRECISSION,4> const &>(*l.begin());
				}
				Vec4(const STARLIGHT_PRECISSION& x,const STARLIGHT_PRECISSION& y,const STARLIGHT_PRECISSION& z,const STARLIGHT_PRECISSION& w)
					:VecBase<Vec4>(){
					data.x=x;
					data.y=y;
					data.z=z;
					data.w=w;
				}
				
				template <class Archive>
				void serialize(Archive & ar){
					ar(cereal::make_nvp("Vec4",data));
				}
			};
		}
	}
}