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
namespace starlight{
	namespace core{
		namespace maths{
			template<typename T>
			struct STARLIGHTAPI VecBase : df::commutative_addable<T>,
				df::commutative_multipliable<T>,
				df::dividable<T>,df::subtractable<T>,
				df::commutative_addable<T,STARLIGHT_PRECISSION>,
				df::commutative_multipliable<T,STARLIGHT_PRECISSION>,
				df::dividable<T,STARLIGHT_PRECISSION>,
				df::subtractable<T,STARLIGHT_PRECISSION>,
				df::totally_ordered<T>{

				T& operator+=(const STARLIGHT_PRECISSION rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension;i++){
						reference.data_array[i]+=rhs;
					}
					return reference;
				}

				T& operator-=(const STARLIGHT_PRECISSION rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension;i++){
						reference.data_array[i]-=rhs;
					}
					return reference;
				}

				T& operator*=(const STARLIGHT_PRECISSION rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension;i++){
						reference.data_array[i]*=rhs;
					}
					return reference;
				}

				T& operator/=(const STARLIGHT_PRECISSION rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension;i++){
						reference.data_array[i]/=rhs;
					}
					return reference;
				}

				T& operator+=(const T& rhs)noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension;i++){
						reference.data_array[i]=reference.data_array[i]+rhs.data_array[i];
					}
					return reference;
				}
				T& operator-=(const T& rhs)noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension;i++){
						reference.data_array[i]=reference.data_array[i]-rhs.data_array[i];
					}
					return reference;
				}
				T& operator*=(const T& rhs)noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension;i++){
						reference.data_array[i]=reference.data_array[i]*rhs.data_array[i];
					}
					return reference;
				}
				T& operator/=(const T& rhs)noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension;i++){
						reference.data_array[i]=reference.data_array[i]/rhs.data_array[i];
					}
					return reference;
				}
				bool operator==(const T& rhs)const noexcept{
					const T& reference(static_cast<const T&>(*this));
					bool result=true;
					for(int i=0; i<T::dimension;i++){
						result&=reference.data_array[i]==rhs.data_array[i];
					}
					return result;
				}
				bool operator<(const T& rhs)const noexcept{
					const T& reference(static_cast<const T&>(*this));
					bool result=false;
					for(int i=0; i<T::dimension;i++){
						if(reference.data_array[i]==rhs.data_array[i]) continue;
						else return reference.data_array[i]<rhs.data_array[i];
					}
					return result;
				}

				static friend std::ostream& operator<< (std::ostream& os,const T& rhs){
					os<<"vec:{";
					for(int i=0; i<T::dimension;i++){
						if(!i) os<<rhs.data_array[i];
						else os<<","<<rhs.data_array[i];
					}
					os<<"}";
					return std::move(os);
				}
				VecBase<T>(){
					T& reference(static_cast<T&>(*this));
					for(int i=0; i<T::dimension;i++)
						reference.data_array[i]=0;
				}

			};

			struct STARLIGHTAPI Vec1 : public VecBase<Vec1>{
				static const short dimension=1;
				union{
					STARLIGHT_PRECISSION data_array[dimension];
					struct _Vec1{
						STARLIGHT_PRECISSION x;
					} data;
				};
				Vec1()=default;
				Vec1(const STARLIGHT_PRECISSION& x)
					:VecBase<Vec1>(){
					data.x=x;
				}
			};

			struct STARLIGHTAPI Vec2 : public VecBase<Vec2>{
				static const short dimension=2;
				union{
					STARLIGHT_PRECISSION data_array[dimension];
					struct _Vec2{
						STARLIGHT_PRECISSION x;
						STARLIGHT_PRECISSION y;
					} data;
				};
				Vec2()=default;
				Vec2(const STARLIGHT_PRECISSION& x,const STARLIGHT_PRECISSION& y)
					:VecBase<Vec2>(){
					data.x=x;
					data.y=y;
				}
			};

			struct STARLIGHTAPI Vec3 : public VecBase<Vec3>{
				static const short dimension=3;
				union{
					STARLIGHT_PRECISSION data_array[dimension];
					struct _Vec3{
						STARLIGHT_PRECISSION x;
						STARLIGHT_PRECISSION y;
						STARLIGHT_PRECISSION z;
					} data;
				};
				Vec3()=default;
				Vec3(const STARLIGHT_PRECISSION& x,const STARLIGHT_PRECISSION& y,const STARLIGHT_PRECISSION& z)
					:VecBase<Vec3>(){
					data.x=x;
					data.y=y;
					data.z=z;
				}
			};
			struct STARLIGHTAPI _Vec4{
				STARLIGHT_PRECISSION x;
				STARLIGHT_PRECISSION y;
				STARLIGHT_PRECISSION z;
				STARLIGHT_PRECISSION w;
			};

			struct STARLIGHTAPI Vec4 : public VecBase<Vec4>{
				
				static const short dimension=4;
				union{
					STARLIGHT_PRECISSION data_array[dimension];
					_Vec4 data;
				};
				Vec4()=default;
				Vec4(const STARLIGHT_PRECISSION& x,const STARLIGHT_PRECISSION& y,const STARLIGHT_PRECISSION& z,const STARLIGHT_PRECISSION& w)
					:VecBase<Vec4>(){
					data.x=x;
					data.y=y;
					data.z=z;
					data.w=w;
				}
				Vec4(const _Vec4& vec)
					:VecBase<Vec4>(){
					data=vec;
				}
			
			};
		}
	}
}