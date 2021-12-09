#' Company : Stevens
#' Project : HW8
#' Purpose : HW8
#' First Name : David
#' Last Name : Fu
#' CWID : 10471854
#' Date : November 22, 2021
#' 
#' 
#' ###### Homework 8 ####
#' 
rm(list=ls())
set.seed(513)
#'
#'
#' Data pre-processing
#'
cancerData=read.csv("/Users/davidfu/Downloads/wisc_bc_ContinuousVar.csv", header=TRUE)

cancerData <- na.omit(cancerData)

cancer_dist<-dist(cancerData[,-2])
hclust_resutls<-hclust(cancer_dist)
plot(hclust_resutls)
hclust_3<-cutree(hclust_resutls,3)
table(hclust_3,cancerData[,5])


kmeans_3<- kmeans(cancerData[,-2],3,nstart = 10)
kmeans_3$cluster
kmeans_3$centers
table(kmeans_3$cluster,cancerData[,5])
#' Memory Clean up
rm(list=ls())

