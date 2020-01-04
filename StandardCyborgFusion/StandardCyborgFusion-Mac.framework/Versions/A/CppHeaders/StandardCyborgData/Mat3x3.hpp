//
//  Mat3x3.hpp
//  StandardCyborgData
//
//  Created by Ricky Reusser on 5/18/19.
//  Copyright © 2019 Standard Cyborg. All rights reserved.
//

#pragma once

#include <vector>

#include <StandardCyborgData/Vec3.hpp>


namespace StandardCyborg {

struct Mat3x4;

struct Mat3x3 {
    // note: we use row-major order for our matrices.
    float m00, m01, m02,
          m10, m11, m12,
          m20, m21, m22;
    
    Mat3x3();
    
    Mat3x3(float m00_, float m01_, float m02_,
           float m10_, float m11_, float m12_,
           float m20_, float m21_, float m22_);
    
    static Mat3x3 Identity();
    static Mat3x3 Zeros();
    
    static Mat3x3 fromColumnMajorVector(const std::vector<float>& data);
    static Mat3x3 fromRowMajorVector(const std::vector<float>& data);
    
    std::vector<float> toColumnMajorVector() const;
    std::vector<float> toRowMajorVector() const;
    
    /* Invert in-place */
    Mat3x3& invert();
    
    /* Return an inverted copy */
    Mat3x3 inverse() const;
    
    static Mat3x3 normalMatrix(const Mat3x4& matrix);
    
    /* Compute whether two matrices are equal to within floating point epsilon */
    static inline bool almostEqual(
        const Mat3x3& lhs,
        const Mat3x3& rhs,
        float relativeTolerance = std::numeric_limits<float>::epsilon(),
        float absoluteTolerance = std::numeric_limits<float>::epsilon()
    );
};

inline Mat3x3 operator*(const Mat3x3& lhs, const Mat3x3& rhs)
{
    return Mat3x3{
        lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20,
        lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21,
        lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22,
        
        lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20,
        lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21,
        lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22,
        
        lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20,
        lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21,
        lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22
    };
}

inline Vec3 operator*(const Mat3x3& lhs, const Vec3& rhs)
{
    return Vec3{
        lhs.m00 * rhs.x + lhs.m01 * rhs.y + lhs.m02 * rhs.z,
        lhs.m10 * rhs.x + lhs.m11 * rhs.y + lhs.m12 * rhs.z,
        lhs.m20 * rhs.x + lhs.m21 * rhs.y + lhs.m22 * rhs.z
    };
}

inline bool operator==(const Mat3x3& lhs, const Mat3x3& rhs)
{
    return lhs.m00 == rhs.m00 && lhs.m01 == rhs.m01 && lhs.m02 == rhs.m02 &&
           lhs.m10 == rhs.m10 && lhs.m11 == rhs.m11 && lhs.m12 == rhs.m12 &&
           lhs.m20 == rhs.m20 && lhs.m21 == rhs.m21 && lhs.m22 == rhs.m22;
}

inline bool operator!=(const Mat3x3& lhs, const Mat3x3& rhs)
{
    return !(lhs == rhs);
}

inline bool Mat3x3::almostEqual(const Mat3x3& lhs, const Mat3x3& rhs, float relativeTolerance, float absoluteTolerance)
{
    return StandardCyborg::almostEqual(lhs.m00, rhs.m00, relativeTolerance, absoluteTolerance) &&
           StandardCyborg::almostEqual(lhs.m01, rhs.m01, relativeTolerance, absoluteTolerance) &&
           StandardCyborg::almostEqual(lhs.m02, rhs.m02, relativeTolerance, absoluteTolerance) &&
           StandardCyborg::almostEqual(lhs.m10, rhs.m10, relativeTolerance, absoluteTolerance) &&
           StandardCyborg::almostEqual(lhs.m11, rhs.m11, relativeTolerance, absoluteTolerance) &&
           StandardCyborg::almostEqual(lhs.m12, rhs.m12, relativeTolerance, absoluteTolerance) &&
           StandardCyborg::almostEqual(lhs.m02, rhs.m02, relativeTolerance, absoluteTolerance) &&
           StandardCyborg::almostEqual(lhs.m20, rhs.m20, relativeTolerance, absoluteTolerance) &&
           StandardCyborg::almostEqual(lhs.m21, rhs.m21, relativeTolerance, absoluteTolerance) &&
           StandardCyborg::almostEqual(lhs.m22, rhs.m22, relativeTolerance, absoluteTolerance);
}

inline Mat3x3 Mat3x3::fromRowMajorVector(const std::vector<float>& data)
{
    return Mat3x3{
        data[0], data[1], data[2],
        data[3], data[4], data[5],
        data[6], data[7], data[8]
    };
}

inline Mat3x3 Mat3x3::fromColumnMajorVector(const std::vector<float>& data)
{
    return Mat3x3{
        data[0], data[3], data[6],
        data[1], data[4], data[7],
        data[2], data[5], data[8]
    };
}

inline std::vector<float> Mat3x3::toColumnMajorVector() const
{
    return std::vector<float>{m00, m10, m20, m01, m11, m21, m02, m12, m22};
}

inline std::vector<float> Mat3x3::toRowMajorVector() const
{
    return std::vector<float>{m00, m01, m02, m10, m11, m12, m20, m21, m22};
}

} // namespace StandardCyborg