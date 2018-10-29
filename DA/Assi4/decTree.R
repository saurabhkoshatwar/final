data = read.csv("daibetes.csv")
dim(data)

sapply(data,class)


# #Missing Values 
# data$Age = ifelse(is.na(data$Age),
#                             ave(data$Age, FUN = function(x) mean(x,na.rm=TRUE)),
#                                  data$Age )

data$Member.type = factor(data$Member.type,levels = c('Casual','Member'),labels = c(1,2))
data$Member.type

#Split
library(caTools)
split = sample.split(Y = data$Member.type,SplitRatio = 0.75)
traindata = subset(data,split==TRUE)
testdata = subset(data,split==FALSE)


# install.packages('e1071')
library(rpart)

classifier = rpart(formula = Member.type~ . ,data = traindata[1:500,])
# y_pred = predict(classifier,testdata[,-9])
testdata[,9]
y_pred = predict(classifier,testdata[,-9],type = 'class')
y_pred


cm = table(testdata[,9],y_pred)
cm

plot(classifier)
text(classifier)
install.packages("rpart.plot")
library(rpart.plot)
rpart.plot(classifier)
rpart.plot(classifier,type=4,extra=101)
pred<-predict(fit,newdata=biker_test,type=("class"))
table(biker_test$Member.type,pred)

