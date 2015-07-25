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

#include <iostream>
#include <initializer_list>
#include <DF\operators.hpp>
#include "STARLIGHT_CORE\Shared.h"
#include "STARLIGHT_CORE\Maths\Vec.h"

namespace starlight{
	namespace core{
		namespace maths{
			static STARLIGHT_PRECISSION toRadians(STARLIGHT_PRECISSION degress){
				return degress* M_PI/180;
			}

			template<typename T>
			struct MatrixBase
				:
				df::commutative_addable<T>,
				df::multipliable<T>,
				df::subtractable<T>,
				df::addable<T,STARLIGHT_PRECISSION>,
				df::multipliable<T,STARLIGHT_PRECISSION>,
				df::dividable<T,STARLIGHT_PRECISSION>,
				df::subtractable<T,STARLIGHT_PRECISSION>,
				df::totally_ordered<T>{

				

				//scalars
				T& operator+=(const STARLIGHT_PRECISSION rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension*T::dimension;i++){
						reference.data_array[i]+=rhs;
					}
					return reference;
				}

				T& operator-=(const STARLIGHT_PRECISSION rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension*T::dimension;i++){
						reference.data_array[i]-=rhs;
					}
					return reference;
				}

				T& operator*=(const STARLIGHT_PRECISSION rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension*T::dimension;i++){
						reference.data_array[i]*=rhs;
					}
					return reference;
				}

				T& operator/=(const STARLIGHT_PRECISSION rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension*T::dimension;i++){
						reference.data_array[i]/=rhs;
					}
					return reference;
				}

				//adders
				T& operator+=(const T& rhs)noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension*T::dimension;i++){
						reference.data_array[i]+=rhs.data_array[i];
					}
					return reference;
				}
				T& operator-=(const T& rhs)noexcept{
					T& reference=static_cast<T&>(*this);
					for(int i=0; i<T::dimension*T::dimension;i++){
						reference.data_array[i]-=rhs.data_array[i];
					}
					return reference;
				}

				//multipyers

				T& operator*=(const T& rhs)noexcept{
					T& reference=static_cast<T&>(*this);
					float data[16];
					for(int y=0; y < 4; y++){
						for(int x=0; x < 4; x++){
							float sum=0.0f;
							for(int e=0; e < 4; e++){
								sum+=reference.data_array[x+e*4]*rhs.data_array[e+y*4];
							}
							data[x+y*4]=sum;
						}
					}
					memcpy(reference.data_array,data,4*4*sizeof(float));

					return reference;
				}
				Vec3 operator*=(const Vec3& rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					return Vec3(
						reference.data[0].x * rhs.data.x+reference.data[1].x * rhs.data.y+reference.data[2].x * rhs.data.z+reference.data[3].x,
						reference.data[0].y * rhs.data.x+reference.data[1].y * rhs.data.y+reference.data[2].y * rhs.data.z+reference.data[3].y,
						reference.data[0].z * rhs.data.x+reference.data[1].z * rhs.data.y+reference.data[2].z * rhs.data.z+reference.data[3].z
						);
				}

				Vec4 operator*=(const Vec4& rhs) noexcept{
					T& reference=static_cast<T&>(*this);
					return Vec4(
						reference.data[0].x * rhs.data.x+reference.data[1].x * rhs.data.y+reference.data[2].x * rhs.data.z+reference.data[3].x * rhs.data.w,
						reference.data[0].y * rhs.data.x+reference.data[1].y * rhs.data.y+reference.data[2].y * rhs.data.z+reference.data[3].y * rhs.data.w,
						reference.data[0].z * rhs.data.x+reference.data[1].z * rhs.data.y+reference.data[2].z * rhs.data.z+reference.data[3].z * rhs.data.w,
						reference.data[0].w * rhs.data.x+reference.data[1].w * rhs.data.y+reference.data[2].w * rhs.data.z+reference.data[3].w * rhs.data.w
						);
				}

				friend Vec3 operator*(const T& reference,const Vec3& rhs){
					return Vec3(
						reference.data[0].x * rhs.data.x+reference.data[1].x * rhs.data.y+reference.data[2].x * rhs.data.z+reference.data[3].x,
						reference.data[0].y * rhs.data.x+reference.data[1].y * rhs.data.y+reference.data[2].y * rhs.data.z+reference.data[3].y,
						reference.data[0].z * rhs.data.x+reference.data[1].z * rhs.data.y+reference.data[2].z * rhs.data.z+reference.data[3].z
						);
				}

				friend Vec4 operator*(const T& reference,const Vec4& rhs){
					return Vec4(
						reference.data[0].x * rhs.data.x+reference.data[1].x * rhs.data.y+reference.data[2].x * rhs.data.z+reference.data[3].x * rhs.data.w,
						reference.data[0].y * rhs.data.x+reference.data[1].y * rhs.data.y+reference.data[2].y * rhs.data.z+reference.data[3].y * rhs.data.w,
						reference.data[0].z * rhs.data.x+reference.data[1].z * rhs.data.y+reference.data[2].z * rhs.data.z+reference.data[3].z * rhs.data.w,
						reference.data[0].w * rhs.data.x+reference.data[1].w * rhs.data.y+reference.data[2].w * rhs.data.z+reference.data[3].w * rhs.data.w
						);
				}



				//equality

				bool operator==(const T& rhs)const noexcept{
					const T& reference(static_cast<const T&>(*this));
					bool result=true;
					for(int i=0; i<T::dimension*T::dimension;i++){
						result&=reference.data_array[i]==rhs.data_array[i];
					}
					return result;
				}
				bool operator<(const T& rhs)const noexcept{
					const T& reference(static_cast<const T&>(*this));
					bool result=false;
					for(int i=0; i<T::dimension*T::dimension;i++){
						if(reference.data_array[i]==rhs.data_array[i]) continue;
						else return reference.data_array[i]<rhs.data_array[i];
					}
					return result;
				}

				//stream
				static friend std::ostream& operator<< (std::ostream& os,const T& rhs){
					os<<"matrix:{";
					for(int i=0; i<T::dimension*T::dimension;i++){
						if(!i) os<<rhs.data_array[i];
						else os<<","<<rhs.data_array[i];
					}
					os<<"}";
					return std::move(os);
				}
				//ctor
				MatrixBase<T>(){
					T& reference(static_cast<T&>(*this));
					for(int i=0; i<T::dimension*T::dimension;i++)
						reference.data_array[i]=0;
				}

				MatrixBase<T>(STARLIGHT_PRECISSION diagonal){
					T& reference(static_cast<T&>(*this));
					for(int i=0; i<T::dimension*T::dimension;i++)
						reference.data_array[i]=0;
					for(int i=0; i<T::dimension;i++)
					reference.data_array[i+i*4]=diagonal;
				}

				static T& identity(){
					return Matrix4Base(1.0f);
				}

			};


			struct Matrix4 : public MatrixBase<Matrix4>{
				static const short dimension=4;
				union{
					STARLIGHT_PRECISSION data_array[dimension*dimension];
					_Vec4 data[dimension];
				};
				Matrix4()=default;
				Matrix4(STARLIGHT_PRECISSION diagonal):MatrixBase(diagonal){}
				
				static Matrix4&  orthographic(STARLIGHT_PRECISSION left,STARLIGHT_PRECISSION right,
										STARLIGHT_PRECISSION bottom,STARLIGHT_PRECISSION top,
										STARLIGHT_PRECISSION near,STARLIGHT_PRECISSION far){
					Matrix4 result(1.0f);

					result.data_array[0+0*4]=2.0f/(right-left);

					result.data_array[1+1*4]=2.0f/(top-bottom);

					result.data_array[2+2*4]=2.0f/(near-far);

					result.data_array[0+3*4]=(left+right)/(left-right);
					result.data_array[1+3*4]=(bottom+top)/(bottom-top);
					result.data_array[2+3*4]=(far+near)/(far-near);

					return std::move(result);
				}

				static Matrix4& Matrix4::perspective(float fov,float aspectRatio,float near,float far){
					Matrix4 result(1.0);

					float q=1.0f/tan(toRadians(0.5f * fov));
					float a=q/aspectRatio;

					float b=(near+far)/(near-far);
					float c=(2.0f * near * far)/(near-far);

					result.data_array[0+0*4]=a;
					result.data_array[1+1*4]=q;
					result.data_array[2+2*4]=b;
					result.data_array[3+2*4]=-1.0f;
					result.data_array[2+3*4]=c;

					return std::move(result);
				}

				static Matrix4& Matrix4::translation(const Vec3& translation){
					Matrix4 result(1.0);

					result.data_array[0+3*4]=translation.data.x;
					result.data_array[1+3*4]=translation.data.y;
					result.data_array[2+3*4]=translation.data.z;

					return std::move(result);
				}

				static Matrix4& Matrix4::rotation(float angle,const Vec3& axis){
					Matrix4 result(1.0);
					float r=toRadians(angle);
					float c=cos(r);
					float s=sin(r);
					float omc=1.0f-c;

					float x=axis.data.x;
					float y=axis.data.y;
					float z=axis.data.z;

					result.data_array[0+0*4]=x * omc+c;
					result.data_array[1+0*4]=y * x * omc+z * s;
					result.data_array[2+0*4]=x * z * omc-y * s;

					result.data_array[0+1*4]=x * y * omc-z * s;
					result.data_array[1+1*4]=y * omc+c;
					result.data_array[2+1*4]=y * z * omc+x * s;

					result.data_array[0+2*4]=x * z * omc+y * s;
					result.data_array[1+2*4]=y * z * omc-x * s;
					result.data_array[2+2*4]=z * omc+c;

					return std::move(result);
				}

				static Matrix4& Matrix4::scale(const Vec3& scale){
					Matrix4 result(1.0);

					result.data_array[0+0*4]=scale.data.x;
					result.data_array[1+1*4]=scale.data.y;
					result.data_array[2+2*4]=scale.data.z;

					return std::move(result);
				}


			};


		}
	}
}