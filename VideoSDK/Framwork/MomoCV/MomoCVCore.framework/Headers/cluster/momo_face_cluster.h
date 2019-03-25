//
//  momo_face_cluster.hpp
//  faceCluster
//
//  Created by 周润楠 on 2018/1/5.
//  Copyright © 2018年 Runnan. All rights reserved.
//

#ifndef momo_face_cluster_hpp
#define momo_face_cluster_hpp

#include <MomoCVCore/api_base/momocv_api.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>

namespace mmcv
{
    /* 聚类需要提供的每张脸的信息 */
    struct MMCV_EXPORT MomoFaceNode
    {
        std::vector<float> feature;     /* 每张人脸提取好的特征，256个float */
        unsigned int faceId;             /* 人脸的Id，一个uint32整数，保证相册中的所有人脸Id唯一 */
        std::string imgId;              /* 该人脸来自于的照片的Id，是一个字符串，保证照片的Id唯一 */
        std::string takeTime;           /* 照片拍摄时间，格式为："2013:03:16 21:36:26" */
        std::vector<float> face_rect;   /* 四个float, 分别表示人脸左上角x，左上角y，右下角x，右下角y */
        std::vector<float> eulerAngle;  /* 三个float, 分别对应人脸的三个欧拉角，顺序为：Pich（上下）、Yaw（左右）、Roll（旋转） */
        int face_ornot;          /*表示当前人脸是否被判定为人脸。0 is face, 1 is notface*/
        int  face_angle_cls;     /*对人脸的角度进行分类，0 is the normal face,1 is the face with small angle， 2 is the face with large angle*/
        
        bool operator<( const MomoFaceNode& other ) const
        {
            return this->faceId < other.faceId;
        }
        
        bool operator==( const MomoFaceNode& other ) const
        {
            return this->faceId == other.faceId;
        }
    };
    
    /* 聚类后的每一类的信息 */
    struct MMCV_EXPORT MomoClusterNode
    {
        std::vector<unsigned int> includeFaceId;    /* 该类中包括的faceId，与momoFaceNode中的faceId对应 */
        std::vector<unsigned int> representFaces;   /* 该类中的代表脸 */
        int clusterId;    /* 代表该cluster绑定的Id，默认为-1，表示该Cluster尚未绑定 */
        std::string coverImageId;      /*代表该 cluster 的原图作为封面, 与MomoFaceNode中的imgId对应 */
        unsigned int coverFaceId;             /* 人脸的Id，一个uint32整数，与MomoFaceNode中faceId对应 */
        std::multimap<float ,int,std::greater<float> > distanceClusterNeighbor;/*distance和clusterId，存储的是其他cluster与该cluster之间的距离，该距离由小到大进行排序*/
    };
    
    struct clusterIDDistance
    {
        int clusterID;//聚类ID
        float distance;//与该聚类ID之间的距离
        clusterIDDistance(int id,float dis);
        bool operator<(const clusterIDDistance& person) const;
    };
    
    class MMCV_EXPORT MomoClusterManger
    {
    public:
        /* 人脸聚类算法的对外接口，faceInfo需要提供全部的人脸信息，clusterInfo如果之前已经聚类过则提供，否则提供空vector */
        void processMomoIncrementCluster(std::vector<MomoFaceNode> &faceList,  std::vector<MomoClusterNode> &clusterList);
        
        void processMomoIncrementCluster_server(std::vector<MomoFaceNode> &faceList,  std::vector<MomoClusterNode> &clusterList);
        
        /* 计算给定ClusterList中的Cluster的RepresentFaces */
        void calcClusterRepesentFaces(std::vector<MomoFaceNode> &faceList, std::vector<MomoClusterNode> &clusterList);
        
        /*返回每个聚类与其他聚类之间的距离，按照从近到远的顺序排列*/
        void calcDistanceClusterNeighbor(std::vector<MomoFaceNode> &faceList, std::vector<MomoClusterNode> &clusterList);
    };
}
#endif /* momo_face_cluster_hpp */

