data = read.csv("daibetes.csv")
data

sapply(data,class)


# #Missing Values 
# data$Age = ifelse(is.na(data$Age),
#                             ave(data$Age, FUN = function(x) mean(x,na.rm=TRUE)),
#                                  data$Age )

data$Outcome = factor(data$Outcome,levels = c(0,1))
data$Outcome


#Split
library(caTools)
split = sample.split(Y = data$Outcome,SplitRatio = 0.80)
traindata = subset(data,split==TRUE)
testdata = subset(data,split==FALSE)


install.packages('caret')
library(e1071)
classifier = naiveBayes(x = traindata[,-9],y = traindata[,9])
y_pred = predict(classifier,testdata[,-9])
y_pred

pr = table(y_pred)
pr
pr1 = pr/nrow(data)
pie(pr1)
box()


cm = table(testdata[,9],y_pred)
cm
accuracy = sum(diag(cm))/sum(cm)
accuracy
library(caret)
confusionMatrix(cm)
