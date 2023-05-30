#include "strategy/strategy_main.h"

void KidsizeStrategy::GetHoleData(const strategy::HoleData &msg)
{
	if(isStart)
	{
		liftandcarryinfo->Hole_x0Flag = msg.Hole_x0Flag;
		liftandcarryinfo->Hole_x1Flag = msg.Hole_x1Flag;
		liftandcarryinfo->Hole_y0Flag = msg.Hole_y0Flag;
		liftandcarryinfo->Hole_y1Flag = msg.Hole_y1Flag;
		liftandcarryinfo->AviodHole = msg.AviodHole;

		liftandcarryinfo->Hole_Leftx1 = msg.Hole_Leftx1;
		liftandcarryinfo->Hole_Rightx1 = msg.Hole_Rightx1;
	}
}

void KidsizeStrategy::GetFootData(const strategy::FootData &msg)
{
	if(isStart)
	{
		liftandcarryinfo->LeftFootDistance = msg.LeftFootDistance;
		liftandcarryinfo->RightFootDistance = msg.RightFootDistance;
		liftandcarryinfo->CenterFootDistance = msg.CenterFootDistance;
		liftandcarryinfo->RightCenterFootDistance = msg.RightCenterFootDistance;
		liftandcarryinfo->LeftCenterFootDistance = msg.LeftCenterFootDistance;

		//liftandcarryinfo->Distance = msg.Distance;
		liftandcarryinfo->NextStairDistance = msg.NextStairDistance;

		LeftSlope2 = msg.LeftSlope2;
		RightSlope2 = msg.RightSlope2;

		liftandcarryinfo->LeftSlopeFlag = msg.LeftSlopeFlag;
		liftandcarryinfo->RightSlopeFlag = msg.RightSlopeFlag;
		liftandcarryinfo->CenterSlopeFlag = msg.CenterSlopeFlag;
		liftandcarryinfo->RightFindWoodFlag = msg.RightFindWoodFlag;
		liftandcarryinfo->LeftFindWoodFlag = msg.LeftFindWoodFlag;

		liftandcarryinfo->DangerLeftFlag = msg.DangerLeftFlag;
		liftandcarryinfo->DangerRightFlag = msg.DangerRightFlag;
		liftandcarryinfo->DangerLeftDistance = msg.DangerLeftDistance;
		liftandcarryinfo->DangerRightDistance = msg.DangerRightDistance;

	}
}

void KidsizeStrategy::SendmainData(int WhichStair, int HeadPostitionY, bool ifinitial, bool HeadState, bool Hardflag, bool Normalflag, bool Easyflag)
{
	strategy::mainData msg;

	msg.WhichStair = WhichStair;
	msg.HeadPostitionY = HeadPostitionY;
	msg.ifinitial = ifinitial;
	msg.HeadState = HeadState;
	msg.Hardflag = Hardflag;
	msg.Normalflag = Normalflag;
	msg.Easyflag = Easyflag;

	mainData_Publish.publish(msg);
}

void KidsizeStrategy::StrategyInitial()
{
	if(liftandcarryinfo->InitialFlag)
	{
		SendBodySector(29);
		liftandcarryinfo->InitialFlag = false;
	}
	if(liftandcarryinfo->WhichStrategy == strategy_liftandcarry)
	{
		liftandcarryinfo->robotPosition.X = 1283/2 + robotPositionXerror + VisionErrorX;
		liftandcarryinfo->robotPosition.Y = 963-robotPositionYerror;

		liftandcarryinfo->Delaytime = 4000;   //here
		liftandcarryinfo->HeadDelaytime = 2000;

		liftandcarryinfo->HeadState = Ini;
		liftandcarryinfo->StrategyState = DecideDistance;
		liftandcarryinfo->WhichStair = Stair_0;
		liftandcarryinfo->BodyState = Find_Wood;
		liftandcarryinfo->HoleState = Left;

		liftandcarryinfo->CaptureTop = false;
		liftandcarryinfo->UpFlag = true;
		liftandcarryinfo->DownFlag = true;
		liftandcarryinfo->BestSFlag = true;
		liftandcarryinfo->RobotUp = true;
		liftandcarryinfo->AviodHole = false;
		liftandcarryinfo->LeftSlopeFlag = false;
		liftandcarryinfo->RightSlopeFlag = false;
		liftandcarryinfo->CenterSlopeFlag = false;
		liftandcarryinfo->FindNextStair = false;
		liftandcarryinfo->SwitchHeadOrBody = true;
		liftandcarryinfo->BackFlag = true;//記得每層都初始
		liftandcarryinfo->LeftFlag = true;
		liftandcarryinfo->RightFlag = true;
		liftandcarryinfo->StopFlag = false;
		liftandcarryinfo->AviodLeftSideFlag = false;
		liftandcarryinfo->AviodRightSideFlag = false;
		liftandcarryinfo->OnsStepFlag = false;
		liftandcarryinfo->StartFlag = false;
		liftandcarryinfo->Easyflag = false;
		liftandcarryinfo->Normalflag = false;
		liftandcarryinfo->Hardflag = false;

		liftandcarryinfo->HeadPostitionX = HeadpositionX;
		liftandcarryinfo->HeadPostitionY = HeadpositionY;

		liftandcarryinfo->TopStair.X = 0;
		liftandcarryinfo->TopStair.Y = 0;
		liftandcarryinfo->TopStair.XMax = 0;
		liftandcarryinfo->TopStair.XMin = 0;
		liftandcarryinfo->TopStair.YMax = 0;
		liftandcarryinfo->TopStair.YMin = 0;

		liftandcarryinfo->SecStair.X = 0;
		liftandcarryinfo->SecStair.Y = 0;
		liftandcarryinfo->SecStair.XMax = 0;
		liftandcarryinfo->SecStair.XMin = 0;
		liftandcarryinfo->SecStair.YMax = 0;
		liftandcarryinfo->SecStair.YMin = 0;

		liftandcarryinfo->TrdStair.X = 0;
		liftandcarryinfo->TrdStair.Y = 0;
		liftandcarryinfo->TrdStair.XMax = 0;
		liftandcarryinfo->TrdStair.XMin = 0;
		liftandcarryinfo->TrdStair.YMax = 0;
		liftandcarryinfo->TrdStair.YMin = 0;

		liftandcarryinfo->FileStair.X = 0;
		liftandcarryinfo->FileStair.Y = 0;
		liftandcarryinfo->FileStair.XMax = 0;
		liftandcarryinfo->FileStair.XMin = 0;
		liftandcarryinfo->FileStair.YMax = 0;
		liftandcarryinfo->FileStair.YMin = 0;

		liftandcarryinfo->LeftFootDistance = (liftandcarryinfo->LeftFoot.YMax) - liftandcarryinfo->LeftForSlope[0];
		liftandcarryinfo->RightFootDistance = (liftandcarryinfo->RightFoot.YMax) -liftandcarryinfo->RightForSlope[0];
		liftandcarryinfo->CenterFootDistance = (liftandcarryinfo->RightFoot.YMax) -liftandcarryinfo->CenterForSlope[0];
		liftandcarryinfo->LeftCenterFootDistance = liftandcarryinfo->LeftFoot.YMax -liftandcarryinfo->LeftCenterForSlope[0];
		liftandcarryinfo->RightCenterFootDistance = liftandcarryinfo->LeftFoot.YMax -liftandcarryinfo->RightCenterForSlope[0];
		liftandcarryinfo->LeftGapDistance = liftandcarryinfo->LeftForSlope[0] - liftandcarryinfo->LeftDistanceSlope[0];
		liftandcarryinfo->RightGapDistance = liftandcarryinfo->RightForSlope[0] - liftandcarryinfo->RightDistanceSlope[0];
		liftandcarryinfo->CenterGapDistance = liftandcarryinfo->CenterForSlope[0] - liftandcarryinfo->CenterDistanceSlope[0];
		liftandcarryinfo->RobotFootSize = 50;

		SendHeadMotor(etHorizontalID,HeadpositionX,400);
		SendHeadMotor(etVerticalID,HeadpositionY,400);
		liftandcarryinfo->DownCount = true;
		//this->twostep
		twostep=0;

		BodyAction(ContinuousStop); 
	}
	else if(liftandcarryinfo->WhichStrategy == strategy_climbingwall)
	{
		if(liftandcarryinfo->InitialFlag)
		{
			SendBodySector(29);
			liftandcarryinfo->InitialFlag = false;
		}
		liftandcarryinfo->Delaytime = 2000;
		liftandcarryinfo->CW_Strategy = Go_to_stair;
		liftandcarryinfo->BodyState = Zero;
		CW_step_flag = true;
		CW_handcheck = false;
		CW_finish = false;
		CW_Stair = 0;
		SendHeadMotor(etHorizontalID,HeadpositionX,400);
		SendHeadMotor(etVerticalID,HeadpositionY,400);
	}
}

void KidsizeStrategy::MainStrategy(int rxMin, int ryMin, int lxMin, int lyMin, int Xcenter, int Ycenter)
{
	float rx,ry,lx,ly;
	int particlenumcount,TopParticleNum_R,SecParticleNum_R,TriParticleNum_R,TopParticleNum_L,SecParticleNum_L,TriParticleNum_L;
	for(int i = 0; i < SampleNum; i++)
	{
		particlenumcount = 0;
		TopParticleNum_R = 0;
		SecParticleNum_R = 0;
		TriParticleNum_R = 0;
		TopParticleNum_L = 0;
		SecParticleNum_L = 0;
		TriParticleNum_L = 0;

		for(int h = 0; h <= 70; h = h + 10)     // 8 times
		{
			for(int w = 0; w <= 45; w = w + 9)  // 6 times      8*6=48
			{
				rx = rxMin + w - Xcenter;   //160 + w - 157
				ry = ryMin + h - Ycenter;   //145 + h - 177

				lx = lxMin + w - Xcenter;
				ly = lyMin + h - Ycenter - 20;

				liftandcarryinfo->Transfer[particlenumcount].rX = (int)((rx)*(cos(liftandcarryinfo->robotMove[i].Theta*PI/180)))+((ry)*(sin(liftandcarryinfo->robotMove[i].Theta*PI/180))) + Xcenter + liftandcarryinfo->robotMove[i].X;
				liftandcarryinfo->Transfer[particlenumcount].rY = (int)((rx)*(-1)*(sin(liftandcarryinfo->robotMove[i].Theta*PI/180)))+((ry)*(cos(liftandcarryinfo->robotMove[i].Theta*PI/180))) + Ycenter + liftandcarryinfo->robotMove[i].Y;

				liftandcarryinfo->Transfer[particlenumcount].lX = (int)((lx)*(cos(liftandcarryinfo->robotMove[i].Theta*PI/180)))+((ly)*(sin(liftandcarryinfo->robotMove[i].Theta*PI/180))) + Xcenter + liftandcarryinfo->robotMove[i].X;
				liftandcarryinfo->Transfer[particlenumcount].lY = (int)((lx)*(-1)*(sin(liftandcarryinfo->robotMove[i].Theta*PI/180)))+((ly)*(cos(liftandcarryinfo->robotMove[i].Theta*PI/180))) + Ycenter + liftandcarryinfo->robotMove[i].Y;
				//旋轉公式是繞著原點旋轉，所以把Xcenter跟Ycenter當成原點rx"ry"lx"ly為相對於中心的座標，最完旋轉之後再加回去再加上前後及左右的平移量

				//right feet area
				switch(strategyinfo->Label_Model[ 320 * liftandcarryinfo->Transfer[particlenumcount].rY + liftandcarryinfo->Transfer[particlenumcount].rX])//ImageUnit->ImageWidth
				{
				case TopColor:
					TopParticleNum_R++;
					break;
				case SecColor:
					SecParticleNum_R++;
					break;
				case TrdColor:
					TriParticleNum_R++;
					break;
				}

				//left feet area
				switch(strategyinfo->Label_Model[ 320 * liftandcarryinfo->Transfer[particlenumcount].lY + liftandcarryinfo->Transfer[particlenumcount].lX])
				{
				case TopColor:
					TopParticleNum_L++;
					break;
				case SecColor:
					SecParticleNum_L++;
					break;
				case TrdColor:
					TriParticleNum_L++;
					break;
				}
				particlenumcount++;
			}
		}
		if(((TopParticleNum_R >= ParticleNum*0.8)&&(TopParticleNum_L >= ParticleNum*0.8))
			||((SecParticleNum_R >= ParticleNum*0.8) && (SecParticleNum_L >= ParticleNum*0.8))
			||((TriParticleNum_R >= ParticleNum*0.8) && (TriParticleNum_L >= ParticleNum*0.8)))
		{
			liftandcarryinfo->CompareMove[liftandcarryinfo->GreatFeetCount] = liftandcarryinfo->robotMove[i];
			liftandcarryinfo->CompareMove[liftandcarryinfo->GreatFeetCount].Value =
				(((float)(abs(liftandcarryinfo->CompareMove[liftandcarryinfo->GreatFeetCount].Y))/30.0)*2.0)
				+ (((float)(90.0-abs(liftandcarryinfo->CompareMove[liftandcarryinfo->GreatFeetCount].Theta - liftandcarryinfo->datum))/90.0)*6.0)
				+ (((float)(25.0-abs(liftandcarryinfo->CompareMove[liftandcarryinfo->GreatFeetCount].X))/30.0)*2.0);
			liftandcarryinfo->GreatFeetCount++;
		}
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	}//for i
}

void KidsizeStrategy::StrategyBody()
{
	liftandcarryinfo->DownHoleFlag = true;
	liftandcarryinfo->ablebodystrategy = true;
	int aa,bb;
 /*if(liftandcarryinfo->BodyState != Spr && liftandcarryinfo->ContinuousFlag)
		BodyAction(ContinuousStop);*/
	switch(liftandcarryinfo->BodyState)
	{
	case Find_Wood:
		if(liftandcarryinfo->WhichStair == Stair_0)
		{
			liftandcarryinfo->BackFlag = true;
			liftandcarryinfo->LeftFlag = true;
			liftandcarryinfo->RightFlag = true;
			liftandcarryinfo->StopFlag = false;
			liftandcarryinfo->UpFlag = false;
			liftandcarryinfo->DownCount = true;
			liftandcarryinfo->rightrotatcount = 0;//++
			liftandcarryinfo->leftrotatcount = 0;
			liftandcarryinfo->shiftcount = 0;
			liftandcarryinfo->Distance = 9999;

			liftandcarryinfo->StrategyState = Select;
		}
		break;
	case Up:
		if (liftandcarryinfo->RobotUp)
		{
			//up
      liftandcarryinfo->BackFlag = true;//記得每層都初始   //如果上坡沒洞請把-1500拿掉!!!!!!!!!!!!!!!!!!!!
			liftandcarryinfo->LeftFlag = true;
			liftandcarryinfo->RightFlag = true;
			liftandcarryinfo->StopFlag = false;
			liftandcarryinfo->UpFlag = false;
			liftandcarryinfo->DownCount = true;
			liftandcarryinfo->rightrotatcount = 0;//++
			liftandcarryinfo->leftrotatcount = 0;
			liftandcarryinfo->shiftcount = 0;
			liftandcarryinfo->Distance = -1000;
			tool->Delay(1000);
			SendBodyAuto(LC_StepX,LC_StepY,0,LC_StepTha,etLC_Step,LC_Stepimu);
		
			//記得最上層要踏很小步。

			liftandcarryinfo->StrategyState = CatchTop;
			liftandcarryinfo->Delaytime = LC_StepDelay;
			liftandcarryinfo->WhichStair++;
			//liftandcarryinfo->BodyState = Walk2Step;  //暫時改
			liftandcarryinfo->BodyState = Zero;  //暫時改
			if (liftandcarryinfo->WhichStair == Stair_3)
			{
				liftandcarryinfo->StrategyState = DecideDownDistance;
				liftandcarryinfo->RobotUp = false;
				liftandcarryinfo->UpFlag = true;
				liftandcarryinfo->DownFlag = false;
			//liftandcarryinfo->BodyState = Walk2Step;  //暫時改
				liftandcarryinfo->BodyState = Zero;  //暫時改
				liftandcarryinfo->TopStair.XMax = 0;
				liftandcarryinfo->TopStair.XMin = 0;
				liftandcarryinfo->TopStair.YMax = 0;
				liftandcarryinfo->TopStair.YMin = 0;
			}
		}
		else
		{
			liftandcarryinfo->NextStairDistance = -1000;
			liftandcarryinfo->StrategyState = DecideDownDistance;
			liftandcarryinfo->BackFlag = true;//記得每層都初始     //如果上坡沒洞請把-1500拿掉!!!!!!!!!!!!!!!!!!!!
			liftandcarryinfo->LeftFlag = true;
			liftandcarryinfo->RightFlag = true;
			liftandcarryinfo->StopFlag = false;
			liftandcarryinfo->DownFlag = false;
			liftandcarryinfo->DownCount = true;
			liftandcarryinfo->rightrotatcount = 0;//++
			liftandcarryinfo->leftrotatcount = 0;
			liftandcarryinfo->shiftcount = 0;
			liftandcarryinfo->AviodLeftSideFlag = false;
			liftandcarryinfo->AviodRightSideFlag = false;
			tool->Delay(1000);
			/*SendBodyAuto(150,0,0,SmallFrontTha,etSingle_wood,SmallFrontimu);
			tool->Delay(3500);*/

			SendBodyAuto(LC_DownX,LC_DownY,0,LC_DownTha,etLC_Down,LC_Downimu);        //如果上坡沒洞請把-1500拿掉!!!!!!!!!!!!!!!!!!!!
			liftandcarryinfo->Delaytime = LC_DownDelay;
			//liftandcarryinfo->BodyState = Walk2Step;  //暫時改
			liftandcarryinfo->BodyState = Zero;  //暫時改
			liftandcarryinfo->WhichStair++;

			if (liftandcarryinfo->WhichStair >= Stair_6)
			{
				liftandcarryinfo->BodyState = Zero;
				liftandcarryinfo->StrategyState = Finish;
			}
		}
		liftandcarryinfo->ablebodystrategy = false;
		break;
	/*case BestWalk:
		xx = ((-1*liftandcarryinfo->CompareMove[0].Y))*0.14*1150;
		bb = ((((-1*liftandcarryinfo->CompareMove[0].Y)*0.14*1000)/4000) + 1);   //如果上坡沒洞請把-1500拿掉!!!!!!!!!!!!!!!!!!!!
		aa = (liftandcarryinfo->CompareMove[0].Theta)/bb;
		liftandcarryinfo->CompareMove[0].Theta = aa;
		//liftandcarryinfo->Delaytime = (((((-1*liftandcarryinfo->CompareMove[0].Y)*0.14) - 1)/2) + 3 + (((int)((-1*liftandcarryinfo->CompareMove[0].Y)*0.14) - 1)%2))*600 + 2000;
		if (liftandcarryinfo->Delaytime < 0)      //如果上坡沒洞請把-1500拿掉!!!!!!!!!!!!!!!!!!!!
		{
			break;
		}
		else
		{
			if (liftandcarryinfo->TopStair.YMax < 85)     //如果上坡沒洞請把-1500拿掉!!!!!!!!!!!!!!!!!!!!
			{
				if (xx<0 || xx>100000)
				{
					SendBodyAuto(2500,0,4000,0,etSingle_wood,etNone) ;//8500
				}
				liftandcarryinfo->Delaytime = 3000;//2200
				//SendBodyAuto((((-1*liftandcarryinfo->CompareMove[0].Y))*0.14*1000)-1500,0,liftandcarryinfo->CompareMove[0].Theta,etSingle_wood);
				SendBodyAuto((((-1*liftandcarryinfo->CompareMove[0].Y))*0.14*1150)*0.5,0,4000,liftandcarryinfo->CompareMove[0].Theta,etSingle_wood,etNone);
				liftandcarryinfo->BodyState = Zero;
			}
			else
			{
				if(twostep==0)
				{
					liftandcarryinfo->Delaytime = 3000;//2500
					SendBodyAuto(2500,0,4000,0,etSingle_wood,etNone);   //如果上坡沒洞請把-1500拿掉!!!!!!!!!!!!!!!!!!!!
					twostep = 1;
					liftandcarryinfo->BodyState = BestWalk;
				}
				else if(twostep==1)
				{
					liftandcarryinfo->Delaytime = 3500;
					if (liftandcarryinfo->TopStair.XMax < liftandcarryinfo->LeftFoot.XMin)
					{
						SendBodyAuto(0,0,4000,20,etSingle_wood,etNone);
					}
					else if(liftandcarryinfo->TopStair.XMin > liftandcarryinfo->RightFoot.XMax)
					{
						SendBodyAuto(0,0,4000,-20,etSingle_wood,etNone);    //如果上坡沒洞請把-1500拿掉!!!!!!!!!!!!!!!!!!!!
					}
					twostep = 0;
					liftandcarryinfo->BodyState = Zero;     //如果上坡沒洞請把-1500拿掉!!!!!!!!!!!!!!!!!!!!
				}
			}
			//liftandcarryinfo->BodyState = Zero;
			//liftandcarryinfo->CaptureTop = false;
		}
		liftandcarryinfo->ablebodystrategy = false;     //如果上坡沒洞請把-1500拿掉!!!!!!!!!!!!!!!!!!!!
		break;*/
	case Hole_:
		liftandcarryinfo->Delaytime = Hole_Delay;
		switch(liftandcarryinfo->HoleState)
		{
		case Left:
			SendBodyAuto(Hole_LeftX,Hole_LeftY,0,Hole_LeftTha,etSingle_third,Hole_Leftimu);
			break;
		case Right:
			SendBodyAuto(Hole_RightX,Hole_RightY,0,Hole_RightTha,etSingle_third,Hole_Rightimu);
			break;
		}
		liftandcarryinfo->BodyState = Zero;
		if (liftandcarryinfo->RobotUp)
			liftandcarryinfo->StrategyState = DecideDistance;
		if (!liftandcarryinfo->RobotUp)
		{
			liftandcarryinfo->OnsStepFlag = true;
			liftandcarryinfo->NextStairDistance = -1000;
		}
		break;
		//liftandcarryinfo->ablebodystrategy = false;//++
	case OnsStep:
		if(liftandcarryinfo->Hole)
		{
			liftandcarryinfo->Delaytime = 4000;
		}
		else
		{
			liftandcarryinfo->Delaytime = 4000;//liftandcarryinfo->CloseY*0.05+800
		}
		OnestepTest++;
		SendBodyAuto(liftandcarryinfo->CloseY,0,0,-1,etSingle_wood,etNone);

		liftandcarryinfo->BodyState = Zero;
		liftandcarryinfo->ablebodystrategy = false;
		break;
		//    case SuperSmallFront:										//This is special case!!!!!!!!!!!!!!!!!!!
		//        liftandcarryinfo->Delaytime = 4000;
		//        SendBodyAuto(SuperSmallFrontX,SuperSmallFrontY,SuperSmallFrontZ,SuperSmallFrontTha,etSingle_wood);//設定成10
		//        liftandcarryinfo->BodyState = Zero;
		//        //liftandcarryinfo->ablebodystrategy = false;//++
	case SmallFront:
		liftandcarryinfo->Delaytime = SmallFrontDelay;
		if(liftandcarryinfo->WhichStair == Stair_0)
		{
			SendBodyAuto(st0_SmallFrontX,st0_SmallFrontY,0,st0_SmallFrontTha,etSingleStep,st0_SmallFrontimu);//設定成20
		}
		else
		{
			SendBodyAuto(SmallFrontX,SmallFrontY,0,SmallFrontTha,etSingle_wood,SmallFrontimu);
		}

		liftandcarryinfo->BodyState = Zero;
		//liftandcarryinfo->ablebodystrategy = false;//++
		break;
	case BigFront:
		liftandcarryinfo->Delaytime = BigFrontDelay;
		if(liftandcarryinfo->WhichStair == Stair_0)
		{
			SendBodyAuto(st0_BigFrontX,st0_BigFrontY,0,st0_BigFrontTha,etSingleStep,st0_BigFrontimu);//設定成40
		}
		else
		{
			SendBodyAuto(BigFrontX,BigFrontY,0,BigFrontTha,etSingle_wood,BigFrontimu);
		}

		liftandcarryinfo->BodyState = Zero;
		//liftandcarryinfo->ablebodystrategy = false;//++
		break;
	case Spr:
		liftandcarryinfo->Delaytime = SprDelay;
		if(liftandcarryinfo->WhichStair == Stair_0)
		{	
			SendBodyAuto(st0_SprX,st0_SprY,0,st0_SprTha,etSingleStep,st0_Sprimu);//設定成60
		}
		else
		{
			SendBodyAuto(SprX,SprY,0,SprTha,etSingle_wood,Sprimu);
			//BodyAction(Continuous, liftandcarryinfo->MoveValue[ContinuousOneStep].X, liftandcarryinfo->MoveValue[ContinuousOneStep].Y, liftandcarryinfo->MoveValue[ContinuousOneStep].Theta);
		}

		liftandcarryinfo->BodyState = Zero;
		//liftandcarryinfo->ablebodystrategy = false;//++
		break;
	case LeftShift:
		liftandcarryinfo->Delaytime = LeftShiftDelay;
		if(liftandcarryinfo->WhichStair == Stair_0)
		{
			SendBodyAuto(LeftShiftX,LeftShiftY,0,LeftShiftTha,etSingle_third,LeftShiftimu);
		}
		else
		{
			SendBodyAuto(LeftShiftX,LeftShiftY,0,LeftShiftTha,etSingle_third,LeftShiftimu);
		}

		liftandcarryinfo->BodyState = Zero;
		if (liftandcarryinfo->special1)//++
		{
			liftandcarryinfo->BodyState = LeftShift;
			liftandcarryinfo->special1 = false;
			liftandcarryinfo->ablebodystrategy = false;
		}
		if(liftandcarryinfo->shiftcount >= 4)
		{
			liftandcarryinfo->BodyState = LeftShift;
			liftandcarryinfo->shiftcount = 0;
			liftandcarryinfo->ablebodystrategy = false;
		}
		//liftandcarryinfo->ablebodystrategy = false;//++
		break;
	case RightShift:
		liftandcarryinfo->Delaytime = RightShiftDelay;
		if(liftandcarryinfo->WhichStair == Stair_0)
		{
			SendBodyAuto(RightShiftX,RightShiftY,0,RightShiftTha,etSingle_third,RightShiftimu);
		}
		else
		{
			SendBodyAuto(RightShiftX,RightShiftY,0,RightShiftTha,etSingle_third,RightShiftimu);
		}

		liftandcarryinfo->BodyState = Zero;
		if (liftandcarryinfo->special1)//++
		{
			liftandcarryinfo->BodyState = RightShift;
			liftandcarryinfo->special1 = false;
			liftandcarryinfo->ablebodystrategy = false;
		}
		if(liftandcarryinfo->shiftcount >= 4)
		{
			liftandcarryinfo->BodyState = RightShift;
			liftandcarryinfo->shiftcount = 0;
			liftandcarryinfo->ablebodystrategy = false;
		}
		//liftandcarryinfo->ablebodystrategy = false;//++
		break;
	case SmallLeftShift:
		liftandcarryinfo->Delaytime = SmallLeftShiftDelay;
		if(liftandcarryinfo->WhichStair == Stair_0)
		{
			SendBodyAuto(SmallLeftShiftX,SmallLeftShiftY,0,SmallLeftShiftTha,etSingle_third,SmallLeftShiftimu);
		}
		else
		{
			SendBodyAuto(SmallLeftShiftX,SmallLeftShiftY,0,SmallLeftShiftTha,etSingle_third,SmallLeftShiftimu);
		}
		liftandcarryinfo->BodyState = Zero;
		//liftandcarryinfo->ablebodystrategy = false;//++
		break;
	case SmallRightShift:
		liftandcarryinfo->Delaytime = SmallRightShiftDelay;
		if(liftandcarryinfo->WhichStair == Stair_0)
		{
			SendBodyAuto(SmallRightShiftX,SmallRightShiftY,0,SmallRightShiftTha,etSingle_third,SmallRightShiftimu);
		}
		else
		{
			SendBodyAuto(SmallRightShiftX,SmallRightShiftY,0,SmallRightShiftTha,etSingle_third,SmallRightShiftimu);
		}
		liftandcarryinfo->BodyState = Zero;
		//liftandcarryinfo->ablebodystrategy = false;//++
		break;
	case SmallLeftRotation:
		liftandcarryinfo->Delaytime = SmallLeftRotationDelay;
		if(liftandcarryinfo->WhichStair == Stair_0)
		{
			SendBodyAuto(SmallLeftRotationX,SmallLeftRotationY,0,SmallLeftRotationTha,etSingle_third,SmallLeftRotationimu);
		}
		else
		{
			SendBodyAuto(SmallLeftRotationX,SmallLeftRotationY,0,SmallLeftRotationTha,etSingle_third,SmallLeftRotationimu);
		}
		liftandcarryinfo->BodyState = Zero;
		liftandcarryinfo->leftrotatcount++;
		if (liftandcarryinfo->leftrotatcount > 4)
		{
			liftandcarryinfo->BodyState = RightShift;
			liftandcarryinfo->ablebodystrategy = false;
			liftandcarryinfo->leftrotatcount = 0;
		}
		//liftandcarryinfo->ablebodystrategy = false;//++
		break;
	case SmallRightRotation:
		liftandcarryinfo->Delaytime = SmallRightShiftDelay;
		if(liftandcarryinfo->WhichStair == Stair_0)
		{
			SendBodyAuto(SmallRightRotationX,SmallRightRotationY,0,SmallRightRotationTha,etSingle_third,SmallRightRotationimu);
		}
		else
		{
			SendBodyAuto(SmallRightRotationX,SmallRightRotationY,0,SmallRightRotationTha,etSingle_third,SmallRightRotationimu);
		}
		liftandcarryinfo->BodyState = Zero;
		liftandcarryinfo->rightrotatcount++;
		if (liftandcarryinfo->rightrotatcount > 4)
		{
			liftandcarryinfo->BodyState = LeftShift;
			liftandcarryinfo->ablebodystrategy = false;
			liftandcarryinfo->rightrotatcount = 0;
		}
		//liftandcarryinfo->ablebodystrategy = false;//++
		break;
	case BigLeftRotation:
		liftandcarryinfo->Delaytime = BigLeftRotationDelay;
		if(liftandcarryinfo->WhichStair == Stair_0)
		{
			SendBodyAuto(BigLeftRotationX,BigLeftRotationY,0,BigLeftRotationTha,etSingle_third,BigLeftRotationimu);
		}
		else
		{
			SendBodyAuto(BigLeftRotationX,BigLeftRotationY,0,BigLeftRotationTha,etSingle_third,BigLeftRotationimu);
		}
		liftandcarryinfo->BodyState = Zero;
		//liftandcarryinfo->ablebodystrategy = false;//++
		break;
	case BigRightRotation:
		liftandcarryinfo->Delaytime = BigRightRotationDelay;
		if(liftandcarryinfo->WhichStair == Stair_0)
		{
			SendBodyAuto(BigRightRotationX,BigRightRotationY,0,BigRightRotationTha,etSingle_third,BigRightRotationimu);
		}
		else
		{
			SendBodyAuto(BigRightRotationX,BigRightRotationY,0,BigRightRotationTha,etSingle_third,BigRightRotationimu);
		}
		liftandcarryinfo->BodyState = Zero;
		//liftandcarryinfo->ablebodystrategy = false;//++
		break;
	case Zero:
		liftandcarryinfo->Delaytime = 0;
		break;
	case Walk2Step:							//原地踏步
		liftandcarryinfo->BodyState = Zero;
		liftandcarryinfo->Delaytime = Walk2StepDelay;
		if(liftandcarryinfo->WhichStair == Stair_0)
		{
			SendBodyAuto(Walk2StepX,Walk2StepY,0,Walk2StepTha,etSingleStep,Walk2Stepimu);
		}
		else
		{
			SendBodyAuto(Walk2StepX,Walk2StepY,0,Walk2StepTha,etSingle_wood,Walk2Stepimu);
		}

		break;
		// case Back:
		//     liftandcarryinfo->Delaytime = 2500;
		//     SendBodyAuto(-1000,0,4000,0,etSingle_wood);
		//     liftandcarryinfo->BodyState = Zero;
		//     liftandcarryinfo->BackFlag = false;
		//     break;
		//
	}
}

void KidsizeStrategy::StrategyHead()
{
	switch(liftandcarryinfo->HeadState)
	{
	case Ini:
		liftandcarryinfo->HeadDelaytime = 2000;//2000
		liftandcarryinfo->HeadPostitionX = HeadpositionX;
		liftandcarryinfo->HeadPostitionY = HeadpositionY;
		SendHeadMotor(etHorizontalID,HeadpositionX,400);
		SendHeadMotor(etVerticalID,HeadpositionY,400);
		//		HeadX = (liftandcarryinfo->HeadPostitionX - 511)/20;
		//		HeadY = (liftandcarryinfo->HeadPostitionY - 278)/20;
		//		HeadfX = (liftandcarryinfo->HeadPostitionX - 511)%20;
		//		HeadfY = (liftandcarryinfo->HeadPostitionY - 278)%20;
		//		for(int i = 0; i < 20; i++)
		//		{
		//			liftandcarryinfo->HeadPostitionX -= HeadX;
		//			liftandcarryinfo->HeadPostitionY -= HeadY;
		//			SendHeadMotor(etHorizontalID,liftandcarryinfo->HeadPostitionX,400);
		//			SendHeadMotor(etVerticalID,liftandcarryinfo->HeadPostitionY,400);
		//		}
		//		liftandcarryinfo->HeadPostitionX -= HeadfX;
		//		liftandcarryinfo->HeadPostitionY -= HeadfY;
		//		SendHeadMotor(etHorizontalID,liftandcarryinfo->HeadPostitionX,400);
		//		SendHeadMotor(etVerticalID,liftandcarryinfo->HeadPostitionY,400);
		liftandcarryinfo->BestSFlag = true;
		liftandcarryinfo->HeadRaiseFlag = false;
		break;
	case Raise:
		liftandcarryinfo->RaiseToIniDelay = true;
		liftandcarryinfo->HeadRaiseFlag = true;
		liftandcarryinfo->HeadDelaytime = 100;
		liftandcarryinfo->BodyState = Zero;
		if (liftandcarryinfo->HeadSwitchY)
		{
			if (liftandcarryinfo->HeadPostitionY <= 1803)
			{
				liftandcarryinfo->HeadPostitionY = liftandcarryinfo->HeadPostitionY + 10;
				liftandcarryinfo->HeadPostitionX = HeadpositionX;
			}
			else
			{
				if (liftandcarryinfo->HeadSwitchX)
				{
					if (liftandcarryinfo->HeadPostitionX <= 2527)		//左
					{
						liftandcarryinfo->HeadPostitionX = liftandcarryinfo->HeadPostitionX + 63;
					}
					else
					{
						liftandcarryinfo->HeadSwitchX = false;
					}
				}
				else
				{
					if (liftandcarryinfo->HeadPostitionX >= 1567)
					{
						liftandcarryinfo->HeadPostitionX = liftandcarryinfo->HeadPostitionX - 83;
					}
					else
					{
						liftandcarryinfo->HeadSwitchX = true;
						liftandcarryinfo->HeadSwitchY = false;
					}
				}
			}
		}
		else
		{
			if (liftandcarryinfo->HeadPostitionY != HeadpositionY)
			{
				liftandcarryinfo->HeadPostitionY = HeadpositionY;
				liftandcarryinfo->HeadPostitionX = HeadpositionX;
			}
			else
			{
				if (liftandcarryinfo->HeadSwitchX)
				{
					if (liftandcarryinfo->HeadPostitionX <= 2527)		//左//刻度有改
					{
						liftandcarryinfo->HeadPostitionX = liftandcarryinfo->HeadPostitionX + 63;
					}
					else
					{
						liftandcarryinfo->HeadSwitchX = false;
					}
				}
				else
				{
					if (liftandcarryinfo->HeadPostitionX >= 1567)
					{
						liftandcarryinfo->HeadPostitionX = liftandcarryinfo->HeadPostitionX - 83;
					}
					else
					{
						liftandcarryinfo->HeadSwitchX = true;		//改到這
						liftandcarryinfo->HeadSwitchY = true;
					}
				}
			}
		}
		SendHeadMotor(etHorizontalID,liftandcarryinfo->HeadPostitionX,100);
		SendHeadMotor(etVerticalID,liftandcarryinfo->HeadPostitionY,100);
		break;
	}
	//HardwareUnit->DoRobotisFlag = true;
}
void KidsizeStrategy::CW_distance()
{
	SendHeadMotor(etHorizontalID,HeadpositionX,400);
	SendHeadMotor(etVerticalID,HeadpositionY,400);

	//initial
	CW_Leftfoot_flag = false;
	CW_Rightfoot_flag = false;
	CW_Leftfoot_distance = 9999 + liftandcarryinfo->LeftFoot.YMax;
	CW_Rightfoot_distance = 9999 + liftandcarryinfo->RightFoot.YMax;

	for(int h = liftandcarryinfo->LeftFoot.YMax; h > 0; h--)
	{
                if(strategyinfo->Label_Model[ ImageWidth * h + liftandcarryinfo->LeftFoot.XMin ] == BlueLabel)
		{
			CW_Leftfoot_distance = liftandcarryinfo->LeftFoot.YMax - h ;
			for (h ; h > 0 ; h--)
			{
                                if(strategyinfo->Label_Model[ ImageWidth * h + liftandcarryinfo->LeftFoot.XMin ] != BlueLabel)
				{
					CW_Slope_Leftdistance = liftandcarryinfo->LeftFoot.YMax - h ;
					break;
				}
			}
			break;
		}
	}
	for(int h = liftandcarryinfo->RightFoot.YMax; h > 0; h--)
	{
                if(strategyinfo->Label_Model[ ImageWidth * h + liftandcarryinfo->RightFoot.XMax ] == BlueLabel)
		{
			CW_Rightfoot_distance = liftandcarryinfo->RightFoot.YMax - h ;
			for (h ; h > 0 ; h--)
			{
                                if(strategyinfo->Label_Model[ ImageWidth * h + liftandcarryinfo->RightFoot.XMax ] != BlueLabel)
				{
					CW_Slope_Rightdistance = liftandcarryinfo->RightFoot.YMax - h ;
					break;
				}
			}
			break;
		}
	}

	CW_Slope = (float)(CW_Slope_Leftdistance - CW_Slope_Rightdistance)/(liftandcarryinfo->RightFoot.XMax - liftandcarryinfo->LeftFoot.XMin)+0.028;

	for(int h = liftandcarryinfo->LeftFoot.YMax; h >= liftandcarryinfo->LeftFoot.YMin; h--)
	{
                if(strategyinfo->Label_Model[ ImageWidth * h + liftandcarryinfo->LeftFoot.XMin ] == BlueLabel)
		{
			CW_Leftfoot_flag = true;
			break;
		}
	}
	for(int h = liftandcarryinfo->RightFoot.YMax; h >= liftandcarryinfo->RightFoot.YMin; h--)
	{
                if(strategyinfo->Label_Model[ ImageWidth * h + liftandcarryinfo->RightFoot.XMax] == BlueLabel)
		{
			CW_Rightfoot_flag = true;
			break;
		}
	}
}

void KidsizeStrategy::CW_StrategyBody()
{
	if(CW_step_flag)
	{
		switch (liftandcarryinfo->BodyState){
		case Spr:
			liftandcarryinfo->Delaytime = SprDelay;
			SendBodyAuto(st0_SprX,st0_SprY,0,st0_SprTha,etSingleStep,st0_Sprimu);
			liftandcarryinfo->BodyState = Zero;
			break;
		case BigLeftRotation:
			liftandcarryinfo->Delaytime = BigLeftRotationDelay;
			SendBodyAuto(BigLeftRotationX,BigLeftRotationY,0,BigLeftRotationTha,etSingle_third,BigLeftRotationimu);
			liftandcarryinfo->BodyState = Zero;
			if(liftandcarryinfo->Laststate == BigRightRotation || liftandcarryinfo->Laststate == SmallRightRotation || liftandcarryinfo->Laststate == SuperSmallRightRotation)
			{
				CW_Count++;
			}
			else
			{
				CW_Count = 0;
			}
			liftandcarryinfo->Laststate = BigLeftRotation;
			break;
		case BigRightRotation:
			liftandcarryinfo->Delaytime = BigRightRotationDelay;
			SendBodyAuto(BigRightRotationX,BigRightRotationY,0,BigRightRotationTha,etSingle_third,BigRightRotationimu);
			liftandcarryinfo->BodyState = Zero;
			if(liftandcarryinfo->Laststate == BigLeftRotation || liftandcarryinfo->Laststate == SmallLeftRotation || liftandcarryinfo->Laststate == SuperSmallLeftRotation)
			{
				CW_Count++;
			}
			else
			{
				CW_Count = 0;
			}
			liftandcarryinfo->Laststate = BigRightRotation;
			break;
		case BigFront:
			liftandcarryinfo->Delaytime = BigFrontDelay;
			SendBodyAuto(st0_BigFrontX,st0_BigFrontY,0,st0_BigFrontTha,etSingleStep,st0_BigFrontimu);
			liftandcarryinfo->BodyState = Zero;
			CW_Count = 0;
			break;
		case SmallFront:
			liftandcarryinfo->Delaytime = SmallFrontDelay;
			SendBodyAuto(st0_SmallFrontX,st0_SmallFrontY,0,st0_SmallFrontTha,etSingleStep,st0_SmallFrontimu);
			CW_Count = 0;
			break;
		case SmallLeftRotation:
			liftandcarryinfo->Delaytime = BigLeftRotationDelay;
			SendBodyAuto(SmallLeftRotationX,SmallLeftRotationY,0,SmallLeftRotationTha,etSingle_third,SmallLeftRotationimu);//設定成10
			liftandcarryinfo->BodyState = Zero;
			if(liftandcarryinfo->Laststate == BigRightRotation || liftandcarryinfo->Laststate == SmallRightRotation || liftandcarryinfo->Laststate == SuperSmallRightRotation)
			{
				CW_Count++;
			}
			else
			{
				CW_Count = 0;
			}
			liftandcarryinfo->Laststate = SmallLeftRotation;
			break;
		case SmallRightRotation:
			liftandcarryinfo->Delaytime = SmallRightRotationDelay;
			SendBodyAuto(SmallRightRotationX,SmallRightRotationY,0,SmallRightRotationTha,etSingle_third,SmallRightRotationimu);
			liftandcarryinfo->BodyState = Zero;
			if(liftandcarryinfo->Laststate == BigLeftRotation || liftandcarryinfo->Laststate == SmallLeftRotation || liftandcarryinfo->Laststate == SuperSmallLeftRotation)
			{
				CW_Count++;
			}
			else
			{
				CW_Count = 0;
			}
			liftandcarryinfo->Laststate = SmallRightRotation;
			break;
		case SuperSmallLeftRotation:
			liftandcarryinfo->Delaytime = 5000;
			SendBodyAuto(SmallLeftRotationX,SmallLeftRotationY,0,int(SmallLeftRotationTha/2),etSingle_third,SmallLeftRotationimu);//設定成10
			liftandcarryinfo->BodyState = Zero;
			if(liftandcarryinfo->Laststate == BigRightRotation || liftandcarryinfo->Laststate == SmallRightRotation || liftandcarryinfo->Laststate == SuperSmallRightRotation)
			{
				CW_Count++;
			}
			else
			{
				CW_Count = 0;
			}
			liftandcarryinfo->Laststate = SuperSmallLeftRotation;
			break;
		case SuperSmallRightRotation:
			liftandcarryinfo->Delaytime = 5000;
			SendBodyAuto(SmallRightRotationX,SmallRightRotationY,0,int(SmallRightRotationTha/2),etSingle_third,SmallRightRotationimu);
			liftandcarryinfo->BodyState = Zero;
			if(liftandcarryinfo->Laststate == BigLeftRotation || liftandcarryinfo->Laststate == SmallLeftRotation || liftandcarryinfo->Laststate == SuperSmallLeftRotation)
			{
				CW_Count++;
			}
			else
			{
				CW_Count = 0;
			}
			liftandcarryinfo->Laststate = SuperSmallRightRotation;
			break;
		case Zero:
			break;
		}
	}
}

void KidsizeStrategy::CW_StrategyClassify()
{
	switch (liftandcarryinfo->CW_Strategy) {
	case Go_to_stair:
		CW_distance();
		if(CW_Count >=4)
		{
				liftandcarryinfo->BodyState = BigFront;
		}
		else if(CW_Leftfoot_flag && CW_Rightfoot_flag)
		{
			if(CW_Leftfoot_distance >= 40 && CW_Rightfoot_distance >= 40)
			{
				liftandcarryinfo->BodyState = BigFront;
			}
			else if(CW_Slope < -0.05)                   //-0.05
			{
				if(abs(CW_Slope) <= 0.2)                //0.2
				{
					liftandcarryinfo->BodyState = SuperSmallLeftRotation;
				}
				else
				{
					if(abs(CW_Slope) <= 0.4)
					{
						liftandcarryinfo->BodyState = SmallLeftRotation;
					}
					else
					{
						liftandcarryinfo->BodyState = BigLeftRotation;	
					}
				}
			}
			else if(CW_Slope > 0.05)                      //0.05
			{
				if(abs(CW_Slope) <= 0.2)
				{
					liftandcarryinfo->BodyState = SuperSmallRightRotation;
				}
				else
				{
					if(abs(CW_Slope) <= 0.4)
					{
						liftandcarryinfo->BodyState = SmallRightRotation;
					}
					else
					{
						liftandcarryinfo->BodyState = BigRightRotation;	
					}
				}
			}
			else if(CW_Leftfoot_distance > CW_Up_distance && CW_Rightfoot_distance > CW_Up_distance)
			{
				liftandcarryinfo->BodyState = SmallFront;
			}
			else if(CW_Leftfoot_distance <= CW_Up_distance && CW_Rightfoot_distance <= CW_Up_distance)       //11
			{
				liftandcarryinfo->CW_Strategy = Climb_to_first_stair;
				liftandcarryinfo->BodyState = Zero;
			}
		}
		else if(CW_Leftfoot_flag && !CW_Rightfoot_flag)			//10
		{
			liftandcarryinfo->BodyState = BigLeftRotation;
		}
		else if(!CW_Leftfoot_flag && CW_Rightfoot_flag)			//01
		{
			liftandcarryinfo->BodyState = BigRightRotation;
		}
		else if(!CW_Leftfoot_flag && !CW_Rightfoot_flag)		//00
		{
			liftandcarryinfo->BodyState = Spr;
		}
		break;
	case Climb_to_first_stair:
		CW_step_flag = false;
		if(!CW_handcheck)
		{
			tool->Delay(2500);
			SendBodyAuto(1500,0,0,0,etSingleStep,etNone);
			tool->Delay(4000);
			SendBodySector(21);
			ROS_INFO("Sector = 21 , delay = %d", CW_first_hand_delay);	//上一階hand
			tool->Delay(CW_first_hand_delay);
			CW_handcheck = true;
		}
		else
		{
			SendBodySector(22);
			ROS_INFO("Sector = 22 , delay = %d", CW_first_foot_delay);	//上一階foot
			tool->Delay(CW_first_foot_delay);
			CW_Stair++;
			CW_finish = true;
			liftandcarryinfo->CW_Strategy = On_stair_top;
			//liftandcarryinfo->CW_Strategy = Climb_to_second_stair;
			CW_handcheck = false;
		}
		break;
	case Climb_to_second_stair:
		if(!CW_handcheck)
		{
			tool->Delay(2000);
			SendBodySector(23);
			ROS_INFO("Sector = 23 , delay = %d", CW_hand_delay);	//上一階hand
			tool->Delay(CW_hand_delay);
			CW_handcheck = true;
		}
		else
		{
			SendBodySector(24);
			ROS_INFO("Sector = 24 , delay = %d", CW_foot_delay);	//上一階foot
			tool->Delay(CW_foot_delay);
			CW_Stair++;
			liftandcarryinfo->CW_Strategy = Climb_next;
			CW_handcheck = false;
		}
		break;
	case Climb_next:
		if(!CW_handcheck)
		{
			tool->Delay(2000);
			SendBodySector(25);
			tool->Delay(2000);
			ROS_INFO("Sector = 25 ");
			tool->Delay(2000);
			SendBodySector(23);
			ROS_INFO("Sector = 23 , delay = %d", CW_hand_delay);
			tool->Delay(CW_hand_delay);
			CW_handcheck = true;
		}
		else
		{
			SendBodySector(24);
			ROS_INFO("Sector = 24 , delay = %d", CW_foot_delay);
			tool->Delay(CW_foot_delay);
			CW_Stair++;
			liftandcarryinfo->CW_Strategy = On_stair_top;
			CW_handcheck = false;
		}

		if(CW_Stair == CW_top_stair)
		{
			CW_finish = true;
			liftandcarryinfo->CW_Strategy = On_stair_top;
		}
		break;
	case On_stair_top:
		ROS_INFO("Already on top of stair!!!");
		break;
	}
}

void KidsizeStrategy::ShowMainData()		//比賽時建議關閉
{
	ROS_INFO("---------------------------");
			//ROS_INFO("etTopColor=%d",ColorMaskSubject[liftandcarryinfo->etTopColor][1].size);
		//ROS_INFO("X = %d", HeadpositionX);
		//ROS_INFO("Y = %d", HeadpositionY);
	ROS_INFO("X = %d", liftandcarryinfo->MoveValue[Continuous].X);
	ROS_INFO("Y = %d", liftandcarryinfo->MoveValue[Continuous].Y);
	ROS_INFO("Theta = %d", liftandcarryinfo->MoveValue[Continuous].Theta);
	ROS_INFO("CloseContinuousFlag = %d", CloseContinuousFlag);
	switch (liftandcarryinfo->WhichStrategy) {
	case strategy_liftandcarry:
		ROS_INFO("WhichStrategy = LC");
		ROS_INFO("HeadRaiseFlag = %s",(liftandcarryinfo->HeadRaiseFlag == true ? "true" : "false"));
		//ROS_INFO("CLOSEY = %d", liftandcarryinfo->CloseY);
		ROS_INFO("Distance = %d",liftandcarryinfo->Distance);
		ROS_INFO("WhichStair = %d",liftandcarryinfo->WhichStair);
		ROS_INFO("NextStairDistance = %d\n",liftandcarryinfo->NextStairDistance);
		ROS_INFO("DangerFlag = %s %s",(liftandcarryinfo->DangerLeftFlag == true ? "true" : "false"),(liftandcarryinfo->DangerRightFlag == true ? "true" : "false"));
		ROS_INFO("DangerDistance = %d %d",liftandcarryinfo->DangerLeftDistance,liftandcarryinfo->DangerRightDistance);
		//ROS_INFO("FindWood = %s %s",(liftandcarryinfo->LeftFindWoodFlag == true ? "true" : "false"),(liftandcarryinfo->RightFindWoodFlag == true ? "true" : "false"));        


		ROS_INFO("AvoidHole = %s",(liftandcarryinfo->AviodHole == true ? "true" : "false"));
		ROS_INFO("Hole_x1 = %d , %d",liftandcarryinfo->Hole_Leftx1,liftandcarryinfo->Hole_Rightx1);
		ROS_INFO("HoleState = %s\n",(liftandcarryinfo->HoleState == true ? "Right" : "Left"));

		ROS_INFO("SlopeFlag = %s %s %s",(liftandcarryinfo->LeftSlopeFlag == true ? "true" : "false"),(liftandcarryinfo->CenterSlopeFlag == true ? "true" : "false"),(liftandcarryinfo->RightSlopeFlag == true ? "true" : "false"));
		ROS_INFO("FootDistance = %d %d %d %d %d",liftandcarryinfo->LeftFootDistance,liftandcarryinfo->CenterFootDistance,liftandcarryinfo->RightFootDistance,liftandcarryinfo->LeftCenterFootDistance,liftandcarryinfo->RightCenterFootDistance);
		ROS_INFO("CaptureTop = %s\n",(liftandcarryinfo->CaptureTop == true ? "true" : "false"));

		switch(liftandcarryinfo->StrategyState){
		case CatchTop:
			ROS_INFO("StrategyState = CatchTop");
			break;
		case DecideDistance:
			ROS_INFO("StrategyState = DicideDistance");
			break;
		case Select:
			ROS_INFO("StrategyState = Select");
			break;
		case BestS:
			ROS_INFO("StrategyState = BestS");
			break;
		case ClosingOnsStep:
			ROS_INFO("StrategyState = ClosingOnsStep");
			break;
		case CalSlope:
			ROS_INFO("StrategyState = CalSlope");
			break;
		case DecideDownDistance:
			ROS_INFO("StrategyState = DecideDownDistance");
			break;
		case Finish:
			ROS_INFO("StrategyState = Finish");
			break;
		default:
			break;
		}

		switch (liftandcarryinfo->HeadState) {
		case Ini:
			ROS_INFO("HeadState = Ini");
			break;
		case Raise:
			ROS_INFO("HeadState = Raise");
			break;
		default:
			break;
		}

		switch (liftandcarryinfo->BodyState) {
		case Spr:
			ROS_INFO("BodyState = Spr\n");
			break;
		case Up:
			ROS_INFO("BodyState = Up\n");
			break;
		case BestWalk:
			ROS_INFO("BodyState = BestWalk\n");
			break;
		case OnsStep:
			ROS_INFO("BodyState = OnsStep\n");
			break;
		case Zero:
			ROS_INFO("BodyState = Zero\n");
			break;
		case SmallFront:
			ROS_INFO("BodyState = SmallFront\n");
			break;
		case SuperSmallFront:
			ROS_INFO("BodyState = SuperSmallFront\n");
			break;
		case SmallLeftRotation:
			ROS_INFO("BodyState = SmallLeftRotation\n");
			break;
		case SmallRightRotation:
			ROS_INFO("BodyState = SmallRightRotation\n");
			break;
		case BigLeftRotation:
			ROS_INFO("BodyState = BigLeftRotation\n");
			break;
		case BigRightRotation:
			ROS_INFO("BodyState = BigRightRotation\n");
			break;
		case RightShift:
			ROS_INFO("BodyState = RightShift\n");
			break;
		case LeftShift:
			ROS_INFO("BodyState = LeftShift\n");
			break;
		case SmallLeftShift:
			ROS_INFO("BodyState = SmallLeftShift\n");
			break;
		case SmallRightShift:
			ROS_INFO("BodyState = SmallRightShift\n");
			break;
		case BigFront:
			ROS_INFO("BodyState = BigFront\n");
			break;
		case Hole_:
			ROS_INFO("BodyState = Hole_\n");
			break;
		case Walk2Step:
			ROS_INFO("BodyState = Walk2Step\n");
			break;
		case Back:
			ROS_INFO("BodyState = Back\n");
			break;
		case Find_Wood:
			ROS_INFO("BodyState = Find_Wood\n");
			break;
		default:
			break;
		}

		break;
	case strategy_climbingwall:
		ROS_INFO("WhichStrategy = CW");
		ROS_INFO("CW_Step = %d",CW_step);
		ROS_INFO("CW_Stair = %d",CW_Stair);
		ROS_INFO("CW_finish = %s",(CW_finish == true ? "true" : "false"));
		ROS_INFO("CW_foot_flag = %s %s",(CW_Leftfoot_flag == true ? "true" : "false"),(CW_Rightfoot_flag == true ? "true" : "false"));
		ROS_INFO("CW_distance = %d %d", CW_Leftfoot_distance, CW_Rightfoot_distance);
		ROS_INFO("CW_Slope = %f\n",CW_Slope);
		ROS_INFO("Count = %d",CW_Count);


		switch (liftandcarryinfo->CW_Strategy) {
		case Go_to_stair:
			ROS_INFO("CW_Strategy_STATE = Go_to_stair");
			break;
		case Climb_to_first_stair:
			ROS_INFO("CW_Strategy_STATE = Climb_to_first_stair");
			break;
		case Climb_to_second_stair:
			ROS_INFO("CW_Strategy_STATE = Climb_to_first_stair");
			break;
		case Climb_next:
			ROS_INFO("CW_Strategy_STATE = Climb_next");
			break;
		case On_stair_top:
			ROS_INFO("CW_Strategy_STATE = On_stair_top");
			break;
		}

		switch (liftandcarryinfo->BodyState) {
		case Spr:
			ROS_INFO("BodyState = Spr\n");
			break;
		case BigLeftRotation:
			ROS_INFO("BodyState = BigLeftRotation\n");
			break;
		case BigRightRotation:
			ROS_INFO("BodyState = BigRightRotation\n");
			break;
		case BigFront:
			ROS_INFO("BodyState = BigFront\n");
			break;
		case SmallFront:
			ROS_INFO("BodyState = SmallFront\n");
			break;
		case SmallLeftRotation:
			ROS_INFO("BodyState = SmallLeftRotation\n");
			break;
		case SmallRightRotation:
			ROS_INFO("BodyState = SmallRightRotation\n");
			break;
		case SuperSmallLeftRotation:
			ROS_INFO("BodyState = SuperSmallLeftRotation\n");
			break;
		case SuperSmallRightRotation:
			ROS_INFO("BodyState = SuperSmallRightRotation\n");
			break;
		case Zero:
			ROS_INFO("BodyState = Zero\n");
			break;
		}
		break;
	}
}

void KidsizeStrategy::StrategyClassify()
{
	for(int i = 0; i < SampleNum; i++)
	{
		liftandcarryinfo->robotMove[i].Theta = rand()%51-25;
		liftandcarryinfo->robotMove[i].X = 0;
		liftandcarryinfo->robotMove[i].Y = rand()%63-63;
	}
	if (liftandcarryinfo->AviodHole && liftandcarryinfo->DownHoleFlag)
	{

		if (liftandcarryinfo->Hole_x0Flag && liftandcarryinfo->Hole_x1Flag && ((liftandcarryinfo->Hole_y0Flag && liftandcarryinfo->Hole_y1Flag) || (liftandcarryinfo->WhichStair == Stair_1)))				//11 11     是洞
		{
			liftandcarryinfo->BodyState = Hole_;
			if ((liftandcarryinfo->Hole_Leftx1 <= liftandcarryinfo->LeftFoot.XMin) && (liftandcarryinfo->Hole_Rightx1 <= liftandcarryinfo->RightFoot.XMax))
			{
				liftandcarryinfo->HoleState = Right;    //洞在左邊 , 往右走
			}
			else if ((liftandcarryinfo->Hole_Leftx1 >= liftandcarryinfo->LeftFoot.XMin) && (liftandcarryinfo->Hole_Rightx1 >= liftandcarryinfo->RightFoot.XMax))
			{
				liftandcarryinfo->HoleState = Left;     //洞在右邊 , 往左走
			}
			else if ((liftandcarryinfo->Hole_Leftx1 > (320 - liftandcarryinfo->Hole_Rightx1)))
			{
				liftandcarryinfo->HoleState = Left;
			}
			else if ((liftandcarryinfo->Hole_Leftx1 <= (320 - liftandcarryinfo->Hole_Rightx1)))
			{
				liftandcarryinfo->HoleState = Right;
			}
		}
		else if (liftandcarryinfo->Hole_x0Flag && !liftandcarryinfo->Hole_x1Flag && ((liftandcarryinfo->Hole_y0Flag && !liftandcarryinfo->Hole_y1Flag) || (liftandcarryinfo->WhichStair == Stair_1)))		//10 10，右移 左邊是洞
		{
			liftandcarryinfo->BodyState = Hole_;
			liftandcarryinfo->HoleState = Right;
		}
		else if (!liftandcarryinfo->Hole_x0Flag && liftandcarryinfo->Hole_x1Flag && ((!liftandcarryinfo->Hole_y0Flag && liftandcarryinfo->Hole_y1Flag) || (liftandcarryinfo->WhichStair == Stair_1)))		//01 01，左移 右邊是洞
		{
			liftandcarryinfo->BodyState = Hole_;
			liftandcarryinfo->HoleState = Left;
		}
		else if (liftandcarryinfo->Hole_x0Flag && liftandcarryinfo->Hole_x1Flag && !liftandcarryinfo->Hole_y0Flag && !liftandcarryinfo->Hole_y1Flag && liftandcarryinfo->WhichStair == Stair_5) //11 00 左右不是洞
		{
			if(liftandcarryinfo->RobotUp)
			{
				liftandcarryinfo->StrategyState = DecideDistance;
			}
			else
			{
				liftandcarryinfo->StrategyState = DecideDownDistance;
			}
			liftandcarryinfo->DownHoleFlag = false;
		}
		else if (liftandcarryinfo->Hole_x0Flag && liftandcarryinfo->Hole_x1Flag && ((liftandcarryinfo->Hole_y0Flag && !liftandcarryinfo->Hole_y1Flag) || (liftandcarryinfo->WhichStair == Stair_1))) //11 10 左邊是洞
		{
			liftandcarryinfo->BodyState = Hole_;
			liftandcarryinfo->HoleState = Right;
		}
		else if (liftandcarryinfo->Hole_x0Flag && liftandcarryinfo->Hole_x1Flag && ((!liftandcarryinfo->Hole_y0Flag && liftandcarryinfo->Hole_y1Flag) || (liftandcarryinfo->WhichStair == Stair_1))) //11 01 右邊是洞
		{
			liftandcarryinfo->BodyState = Hole_;
			liftandcarryinfo->HoleState = Left;
		}
		else if (liftandcarryinfo->Hole_x0Flag && !liftandcarryinfo->Hole_x1Flag && !liftandcarryinfo->Hole_y0Flag && !liftandcarryinfo->Hole_y1Flag && liftandcarryinfo->WhichStair == Stair_5) //10 00 左右不是洞
		{
			if(liftandcarryinfo->RobotUp)
			{
				liftandcarryinfo->StrategyState = DecideDistance;
			}
			else
			{
				liftandcarryinfo->StrategyState = DecideDownDistance;
			}
			liftandcarryinfo->DownHoleFlag = false;
		}
		else if (!liftandcarryinfo->Hole_x0Flag && liftandcarryinfo->Hole_x1Flag && !liftandcarryinfo->Hole_y0Flag && !liftandcarryinfo->Hole_y1Flag && liftandcarryinfo->WhichStair == Stair_5) //01 00 左右不是洞
		{
			if(liftandcarryinfo->RobotUp)
			{
				liftandcarryinfo->StrategyState = DecideDistance;
			}
			else
			{
				liftandcarryinfo->StrategyState = DecideDownDistance;
			}
			liftandcarryinfo->DownHoleFlag = false;
		}
		liftandcarryinfo->AviodHole = false;
		if (liftandcarryinfo->RobotUp)
		{
			liftandcarryinfo->StrategyState = DecideDistance;
		}
		else
		{
			liftandcarryinfo->StrategyState = DecideDownDistance;
		}
	}
	else if(!liftandcarryinfo->UpFlag || !liftandcarryinfo->DownFlag)
	{
		//printf("case %d\n", liftandcarryinfo->StrategyState);
		switch(liftandcarryinfo->StrategyState)
		{
		case CatchTop:
			if(liftandcarryinfo->ablebodystrategy) //原本是要註解掉的//
			{		
				liftandcarryinfo->CaptureTop = false;
				//liftandcarryinfo->getimage = true;
				strategyinfo->getimage = true;
				liftandcarryinfo->MaxTopSize = 1000;
				
				//printf("color cnt = %d\n", strategyinfo->ColorMaskSubjectCnt[liftandcarryinfo->etTopColor]);
				for (int i = 0; i < strategyinfo->ColorMaskSubjectCnt[liftandcarryinfo->etTopColor]; i++)
				{	
					//printf("size = %d\n", strategyinfo->ColorMaskSubject[liftandcarryinfo->etTopColor][i].size);
					if (strategyinfo->ColorMaskSubject[liftandcarryinfo->etTopColor][i].size > liftandcarryinfo->MaxTopSize)
					{
						//printf("size = %d\n", ColorMaskSubject[liftandcarryinfo->etTopColor][i].size);
						liftandcarryinfo->MaxTopSize = strategyinfo->ColorMaskSubject[liftandcarryinfo->etTopColor][i].size;
						liftandcarryinfo->TopStair.X = (strategyinfo->ColorMaskSubject[liftandcarryinfo->etTopColor][i].XMin + ColorMaskSubject[liftandcarryinfo->etTopColor][i].XMax)/2;
						liftandcarryinfo->TopStair.Y = (strategyinfo->ColorMaskSubject[liftandcarryinfo->etTopColor][i].YMin + ColorMaskSubject[liftandcarryinfo->etTopColor][i].YMax)/2;
						liftandcarryinfo->TopStair.XMin = strategyinfo->ColorMaskSubject[liftandcarryinfo->etTopColor][i].XMin;
						liftandcarryinfo->TopStair.XMax = strategyinfo->ColorMaskSubject[liftandcarryinfo->etTopColor][i].XMax;
						liftandcarryinfo->TopStair.YMin = strategyinfo->ColorMaskSubject[liftandcarryinfo->etTopColor][i].YMin;
						liftandcarryinfo->TopStair.YMax = strategyinfo->ColorMaskSubject[liftandcarryinfo->etTopColor][i].YMax;

						liftandcarryinfo->CaptureTop = true;
						strategyinfo->getimage = false;	//???
						if (liftandcarryinfo->HeadState == Raise)
						{
							liftandcarryinfo->HeadRaiseFlag = true;
							liftandcarryinfo->HeadState = Ini;
							//liftandcarryinfo->StrategyState = BestS;
							liftandcarryinfo->StrategyState = DecideDistance;
						}
					}
				}
				if (liftandcarryinfo->HeadState == Ini)
				{
					liftandcarryinfo->Distance = 1000;
					liftandcarryinfo->StrategyState = DecideDistance;
				}
				else if (liftandcarryinfo->HeadState == Raise)
				{
					liftandcarryinfo->HeadRaiseFlag = true;
					liftandcarryinfo->StrategyState = Select;
				}
			}
			break;
		case DecideDistance:
		// if(!liftandcarryinfo->ContinuousFlag)tool->Delay(1000);
			countdistance = 0;
			if(liftandcarryinfo->WhichStair == Stair_0)
			{
				for( int h = liftandcarryinfo->LeftFoot.YMin+30; h > 0 ; h-- )
				{
					if( strategyinfo->Label_Model[ ImageWidth * h + liftandcarryinfo->LeftFoot.XMin ] == TrdColor )
					{
						liftandcarryinfo->LeftForSlope[0] = h;
						countdistance++;
						if (countdistance>14)
						{
							countdistance = 0;
							break;
						}
					}
				}
				for( int h = liftandcarryinfo->LeftFoot.YMax - 30; h > 0 ; h-- )
				{
					if( strategyinfo->Label_Model[ ImageWidth * h + ((liftandcarryinfo->LeftFoot.XMin + liftandcarryinfo->RightFoot.XMax)/2) ] == TrdColor )
					{
						liftandcarryinfo->CenterForSlope[0] = h;
						countdistance++;
						if (countdistance>14)
						{
							countdistance = 0;
							break;
						}
					}
				}
				for( int h = liftandcarryinfo->RightFoot.YMin+30; h > 0 ; h-- )
				{
					if( strategyinfo->Label_Model[ ImageWidth * h + liftandcarryinfo->RightFoot.XMax ] == TrdColor )
					{
						liftandcarryinfo->RightForSlope[0] = h;
						countdistance++;
						if (countdistance>14)
						{
							countdistance = 0;
							break;
						}
					}
				}
			}
			else if(liftandcarryinfo->WhichStair == Stair_1)
			{
				for( int h = liftandcarryinfo->LeftFoot.YMin+30; h > 0 ; h-- )
				{
					if( strategyinfo->Label_Model[ ImageWidth * h + liftandcarryinfo->LeftFoot.XMin ] == SecColor )
					{
						liftandcarryinfo->LeftForSlope[0] = h;
						countdistance++;
						if (countdistance>14)
						{
							countdistance = 0;
							break;
						}
					}
				}
				for( int h = liftandcarryinfo->LeftFoot.YMax - 30; h > 0 ; h-- )
				{
					if( strategyinfo->Label_Model[ ImageWidth * h + ((liftandcarryinfo->LeftFoot.XMin + liftandcarryinfo->RightFoot.XMax)/2) ] == SecColor )
					{
						liftandcarryinfo->CenterForSlope[0] = h;
						countdistance++;
						if (countdistance>14)
						{
							countdistance = 0;
							break;
						}
					}
				}
				for( int h = liftandcarryinfo->RightFoot.YMin+30; h > 0 ; h-- )
				{
					if( strategyinfo->Label_Model[ ImageWidth * h + liftandcarryinfo->RightFoot.XMax ] == SecColor )
					{
						liftandcarryinfo->RightForSlope[0] = h;
						countdistance++;
						if (countdistance>14)
						{
							countdistance = 0;
							break;
						}
					}
				}
			}
			else if(liftandcarryinfo->WhichStair == Stair_2)
			{
				for( int h = liftandcarryinfo->LeftFoot.YMin+30; h > 0 ; h-- )
				{
					if( strategyinfo->Label_Model[ ImageWidth * h + liftandcarryinfo->LeftFoot.XMin ] == TopColor )
					{
						liftandcarryinfo->LeftForSlope[0] = h;
						countdistance++;
						if (countdistance>14)
						{
							countdistance = 0;
							break;
						}
					}
				}
				for( int h = liftandcarryinfo->LeftFoot.YMax - 30; h > 0 ; h-- )
				{
					if( strategyinfo->Label_Model[ ImageWidth * h + ((liftandcarryinfo->LeftFoot.XMin + liftandcarryinfo->RightFoot.XMax)/2) ] == TopColor )
					{
						liftandcarryinfo->CenterForSlope[0] = h;
						countdistance++;
						if (countdistance>14)
						{
							countdistance = 0;
							break;
						}
					}
				}
				for( int h = liftandcarryinfo->RightFoot.YMin+30; h > 0 ; h-- )
				{
					if( strategyinfo->Label_Model[ ImageWidth * h + liftandcarryinfo->RightFoot.XMax ] == TopColor )
					{
						liftandcarryinfo->RightForSlope[0] = h;
						countdistance++;
						if (countdistance>14)
						{
							countdistance = 0;
							break;
						}
					}
				}
			}
			if (liftandcarryinfo->LeftForSlope[0] > liftandcarryinfo->RightForSlope[0])
			{
				MaxSlop = liftandcarryinfo->LeftForSlope[0];
			}
			else
			{
				MaxSlop = liftandcarryinfo->RightForSlope[0];
			}
			if (MaxSlop < liftandcarryinfo->CenterForSlope[0])
			{
				MaxSlop = liftandcarryinfo->CenterForSlope[0];
			}
			liftandcarryinfo->Distance = liftandcarryinfo->LeftFoot.YMax - MaxSlop;



			liftandcarryinfo->LeftForSlope[0] = -9999 + liftandcarryinfo->LeftFoot.YMax;//!!!
			liftandcarryinfo->RightForSlope[0] = -9999 + liftandcarryinfo->LeftFoot.YMax;//初始
			liftandcarryinfo->CenterForSlope[0] = -9999 + liftandcarryinfo->LeftFoot.YMax;
			liftandcarryinfo->LeftCenterForSlope[0] = -9999 + liftandcarryinfo->LeftFoot.YMax;
			liftandcarryinfo->RightCenterForSlope[0] = -9999 + liftandcarryinfo->LeftFoot.YMax;
			liftandcarryinfo->StrategyState = Select;
			break;
		case Select://如果比賽頭軟掉來不及修就直接用攝影機設定基礎位置，再強制讓他進入第1個if，後面兩個else if直接註解掉。
			// if(liftandcarryinfo->Distance <= UpDistance)// && liftandcarryinfo->Distance > 0 || liftandcarryinfo->WhichStair == Stair_0 || liftandcarryinfo->WhichStair == Stair_1 || liftandcarryinfo->WhichStair == Stair_2 && liftandcarryinfo->Distance > 0 || liftandcarryinfo->WhichStair == Stair_0 || liftandcarryinfo->WhichStair == Stair_1 || liftandcarryinfo->WhichStair == Stair_2)
			// {
			// 	liftandcarryinfo->HeadState = Ini;
			// 	if(liftandcarryinfo->WhichStair == Stair_0) 
        	// 	{ 
          	// 		liftandcarryinfo->StrategyState = ClosingOnsStep;      //加速
        	// 	} 
        	// 	else 
        	// 	{ 
			// 					liftandcarryinfo->StrategyState = CalSlope;
        	// 	}
			// 	//liftandcarryinfo->StrategyState = ClosingOnsStep;//20161023  
			// 	//liftandcarryinfo->StrategyState = CalSlope;        //20180328
			// }
			// else if (liftandcarryinfo->Distance > UpDistance && liftandcarryinfo->CaptureTop == false /*&& liftandcarryinfo->WhichStair != Stair_0*/)//大無
			// {
			// 	liftandcarryinfo->HeadState = Raise;
			// 	liftandcarryinfo->StrategyState = CatchTop;
			// }
			// else if(liftandcarryinfo->Distance > UpDistance && liftandcarryinfo->CaptureTop == true)//大有
			// {
			// 	liftandcarryinfo->HeadState = Ini;
			// 	liftandcarryinfo->StrategyState = BestS;
			// }
			// else
			// {
			// 	liftandcarryinfo->StrategyState = DecideDistance;
			// }
			liftandcarryinfo->StrategyState = CalSlope;
			break; 
		case BestS:
			if (liftandcarryinfo->BestSFlag)
			{
				liftandcarryinfo->BestSFlag = false;
				liftandcarryinfo->datum = 0;
				if(liftandcarryinfo->RobotUp)
				{
					if(liftandcarryinfo->TopStair.X < liftandcarryinfo->robotPosition.X )
						liftandcarryinfo->datum = acos((liftandcarryinfo->robotPosition.Y-liftandcarryinfo->TopStair.Y)/sqrt(pow(liftandcarryinfo->TopStair.X-liftandcarryinfo->robotPosition.X,2)+pow(liftandcarryinfo->TopStair.Y-liftandcarryinfo->robotPosition.Y,2)))/(PI)*180;
					else if(liftandcarryinfo->TopStair.X > liftandcarryinfo->robotPosition.X  )
						liftandcarryinfo->datum = -1*acos((liftandcarryinfo->robotPosition.Y-liftandcarryinfo->TopStair.Y)/sqrt(pow(liftandcarryinfo->TopStair.X-liftandcarryinfo->robotPosition.X,2)+pow(liftandcarryinfo->TopStair.Y-liftandcarryinfo->robotPosition.Y,2)))/(PI)*180;
					else
						liftandcarryinfo->datum = 0;
				}
				liftandcarryinfo->GreatFeetCount = 0;

				MainStrategy(liftandcarryinfo->RightFoot.XMin ,liftandcarryinfo->RightFoot.YMin,liftandcarryinfo->LeftFoot.XMin ,liftandcarryinfo->LeftFoot.YMin,liftandcarryinfo->FeetXcenter,liftandcarryinfo->FeetYcenter);		//LiftAndCarryInfo.cpp初始，之後沒改

				liftandcarryinfo->bubble(liftandcarryinfo->GreatFeetCount,liftandcarryinfo->CompareMove);//排序完CompareMove[0]為最佳腳
				liftandcarryinfo->TESTRotation_matrix(liftandcarryinfo->RightFoot.XMin ,liftandcarryinfo->RightFoot.YMin,liftandcarryinfo->LeftFoot.XMin ,liftandcarryinfo->LeftFoot.YMin,liftandcarryinfo->FeetXcenter,liftandcarryinfo->FeetYcenter,liftandcarryinfo->CompareMove,0,0);
				liftandcarryinfo->TESTRotation_matrix(liftandcarryinfo->RightFoot.XMax ,liftandcarryinfo->RightFoot.YMin,liftandcarryinfo->LeftFoot.XMax,liftandcarryinfo->LeftFoot.YMin,liftandcarryinfo->FeetXcenter ,liftandcarryinfo->FeetYcenter,liftandcarryinfo->CompareMove,1,0);
				liftandcarryinfo->TESTRotation_matrix(liftandcarryinfo->RightFoot.XMin ,liftandcarryinfo->RightFoot.YMax,liftandcarryinfo->LeftFoot.XMin ,liftandcarryinfo->LeftFoot.YMax,liftandcarryinfo->FeetXcenter,liftandcarryinfo->FeetYcenter,liftandcarryinfo->CompareMove,2,0);
				liftandcarryinfo->TESTRotation_matrix(liftandcarryinfo->RightFoot.XMax ,liftandcarryinfo->RightFoot.YMax,liftandcarryinfo->LeftFoot.XMax,liftandcarryinfo->LeftFoot.YMax,liftandcarryinfo->FeetXcenter ,liftandcarryinfo->FeetYcenter,liftandcarryinfo->CompareMove,3,0);


				if ((liftandcarryinfo->Distance <= PrepareUpDistance) && (liftandcarryinfo->GreatFeetCount <= 25))//JJ
				{
					liftandcarryinfo->StrategyState = DecideDistance;
				}
				else if(liftandcarryinfo->GreatFeetCount == 0)
				{
					liftandcarryinfo->StrategyState = ClosingOnsStep;
				}
				else
				{
					liftandcarryinfo->BodyState = Spr;//BestWalk
					liftandcarryinfo->StrategyState = CatchTop;
					liftandcarryinfo->ablebodystrategy = false; //Best 
				}
			}
			break;
		case ClosingOnsStep:				
			if(liftandcarryinfo->Distance > 60) //try ay night
      		{ 
				if(CloseContinuousFlag)
				{
        			BodyAction(Continuous, liftandcarryinfo->MoveValue[ContinuousMaxValue].X, 0, liftandcarryinfo->MoveValue[ContinuousMaxValue].Theta);
				}
				else
				{
					SendBodyAuto(5500,0,0,0,etSingleStep,etRoll);
					tool->Delay(3500);
				} 
      			//return;
			}    
			 /*if (liftandcarryinfo->Distance > 200)		//所以至多走到185
			 {
			     liftandcarryinfo->CloseY = 14500;
			 }
			 else if (liftandcarryinfo->Distance > 185)	//所以至多走到170
			 {
			     liftandcarryinfo->CloseY = 13500;
			 }
			 else if (liftandcarryinfo->Distance > 170)	//所以至多走到155
			 {
			     liftandcarryinfo->CloseY = 12100;
			 }
			 else if (liftandcarryinfo->Distance > 155)	//所以至多走到140
			 {
			     liftandcarryinfo->CloseY = 10600;
			 }
			 else if (liftandcarryinfo->Distance > 140)	//所以至多走到125
			 {
			     liftandcarryinfo->CloseY = 9800;
			 }
			 else if (liftandcarryinfo->Distance > 125)	//所以至多走到110
			 {
			     liftandcarryinfo->CloseY = 8300;
			 }
			 else if (liftandcarryinfo->Distance > 110)	//所以至多走到95
			 {
			     liftandcarryinfo->CloseY = 6900;
			 }
			 else if (liftandcarryinfo->Distance > 95)	//所以至多走到80
			 {
			     liftandcarryinfo->CloseY = 5500;
			 }*/
			else
			{
				BodyAction(ContinuousStop);
				liftandcarryinfo->StrategyState = CalSlope;
				return;
			}
			liftandcarryinfo->BodyState = Zero;
			liftandcarryinfo->StrategyState = DecideDistance;//看情況改回CalSlope
			/*liftandcarryinfo->StrategyState = CalSlope;
			liftandcarryinfo->ablebodystrategy = false;*/
			break;
		case CalSlope:
			if (liftandcarryinfo->WhichStair >=  Stair_6)
			{
				liftandcarryinfo->BodyState = Zero;
				break;
			}
			RightSlope1 = (float)(liftandcarryinfo->RightFootDistance - liftandcarryinfo->CenterFootDistance)/50;
			LeftSlope1 = (float)(liftandcarryinfo->LeftFootDistance - liftandcarryinfo->CenterFootDistance)/-50;
			if (liftandcarryinfo->LeftSlopeFlag && liftandcarryinfo->CenterForSlope && liftandcarryinfo->RightSlopeFlag)//111
			{
				if (liftandcarryinfo->RobotUp)			//up
				{
					if(!liftandcarryinfo->DangerLeftFlag && !liftandcarryinfo->DangerRightFlag)
					{
						if ((liftandcarryinfo->LeftFootDistance <= SureUpDistance) && (liftandcarryinfo->CenterFootDistance <= SureUpDistance) && (liftandcarryinfo->RightFootDistance <= SureUpDistance)) //111
						{
							liftandcarryinfo->BodyState = Up;
							//liftandcarryinfo->UpFlag = true;
							liftandcarryinfo->StrategyState = CatchTop;
						}
						else if ((liftandcarryinfo->LeftFootDistance > 60) && (liftandcarryinfo->CenterFootDistance > 60) && (liftandcarryinfo->RightFootDistance > 60))
						{
							liftandcarryinfo->BodyState = Spr;
						}
						else if ((liftandcarryinfo->LeftFootDistance > 40) && (liftandcarryinfo->CenterFootDistance > 40) && (liftandcarryinfo->RightFootDistance > 40))//000
						{
							liftandcarryinfo->BodyState = BigFront;//大直走
						}
						else if ((liftandcarryinfo->LeftFootDistance > SureUpDistance) && (liftandcarryinfo->CenterFootDistance > SureUpDistance) && (liftandcarryinfo->RightFootDistance > SureUpDistance))//000
						{
							liftandcarryinfo->BodyState = SmallFront;//小直走
						}
						else if ((liftandcarryinfo->LeftFootDistance > SureUpDistance) && (liftandcarryinfo->CenterFootDistance <= SureUpDistance) && (liftandcarryinfo->RightFootDistance <= SureUpDistance))		//011
						{
							if ((liftandcarryinfo->LeftFootDistance <= SureUpDistance + 10) || (liftandcarryinfo->LeftCenterFootDistance <= SureUpDistance+5))
							{
								liftandcarryinfo->BodyState = Up;
								//liftandcarryinfo->UpFlag = true;
								liftandcarryinfo->StrategyState = CatchTop;
							}
							else
							{
								liftandcarryinfo->BodyState = SmallRightRotation;
							}
						}
						else if ((liftandcarryinfo->LeftFootDistance <= SureUpDistance) && (liftandcarryinfo->CenterFootDistance > SureUpDistance) && (liftandcarryinfo->RightFootDistance <= SureUpDistance))		//101
						{
							if (liftandcarryinfo->CenterFootDistance <= (SureUpDistance + 5))
							{
								liftandcarryinfo->BodyState = Up;
								//liftandcarryinfo->UpFlag = true;
								liftandcarryinfo->StrategyState = CatchTop;
							}
							else
							{
								if (liftandcarryinfo->LeftCenterFootDistance <= SureUpDistance && liftandcarryinfo->RightCenterFootDistance <= SureUpDistance)//11
								{
									liftandcarryinfo->BodyState = Up;
									//liftandcarryinfo->UpFlag = true;
									liftandcarryinfo->StrategyState = CatchTop;
								}
								else if (liftandcarryinfo->LeftCenterFootDistance > SureUpDistance && liftandcarryinfo->RightCenterFootDistance <= SureUpDistance)//01
								{
									liftandcarryinfo->BodyState = SmallRightRotation;//新增左右璇會前進一點;
								}
								else if (liftandcarryinfo->LeftCenterFootDistance <= SureUpDistance && liftandcarryinfo->RightCenterFootDistance > SureUpDistance)//10
								{
									liftandcarryinfo->BodyState = SmallLeftRotation;
								}
								else
								{
									liftandcarryinfo->BodyState = SmallFront;
								}
							}
						}
						else if ((liftandcarryinfo->LeftFootDistance > SureUpDistance) && (liftandcarryinfo->CenterFootDistance > SureUpDistance) && (liftandcarryinfo->RightFootDistance <= SureUpDistance))		//001
						{
							if ((liftandcarryinfo->LeftFootDistance - liftandcarryinfo->CenterFootDistance > 16)||((liftandcarryinfo->CenterFootDistance > SureUpDistance + 12) ))//30度  && (liftandcarryinfo->LeftFootDistance > SureUpDistance + 15)
							{
								liftandcarryinfo->BodyState = BigRightRotation;
							}
							else if(liftandcarryinfo->LeftFootDistance - liftandcarryinfo->CenterFootDistance > 6)//15度
							{
								liftandcarryinfo->BodyState = SmallRightRotation;
							}
							else
							{
								if (liftandcarryinfo->CenterFootDistance - liftandcarryinfo->RightFootDistance > 15 && liftandcarryinfo->LeftFootDistance - liftandcarryinfo->RightFootDistance > 30)
								{
									liftandcarryinfo->BodyState = BigRightRotation;
								}
								else if (liftandcarryinfo->CenterFootDistance - liftandcarryinfo->RightFootDistance > 6 && liftandcarryinfo->LeftFootDistance - liftandcarryinfo->RightFootDistance > 12)
								{
									liftandcarryinfo->BodyState = SmallRightRotation;
								}
								else
								{
									liftandcarryinfo->BodyState = SmallFront;
								}
							}
						}
						else if ((liftandcarryinfo->LeftFootDistance <= SureUpDistance) && (liftandcarryinfo->CenterFootDistance <= SureUpDistance) && (liftandcarryinfo->RightFootDistance > SureUpDistance))		//110
						{
							if ((liftandcarryinfo->RightFootDistance <= SureUpDistance + 10) || (liftandcarryinfo->RightCenterFootDistance <= SureUpDistance + 5))
							{
								liftandcarryinfo->BodyState = Up;
								//liftandcarryinfo->UpFlag = true;
								liftandcarryinfo->StrategyState = CatchTop;
							}
							else
							{
								liftandcarryinfo->BodyState = SmallLeftRotation;
							}
						}
						else if ((liftandcarryinfo->LeftFootDistance > SureUpDistance) && (liftandcarryinfo->CenterFootDistance <= SureUpDistance) && (liftandcarryinfo->RightFootDistance > SureUpDistance))		//010
						{
							if (liftandcarryinfo->LeftFootDistance <= (SureUpDistance + 6) && liftandcarryinfo->RightFootDistance <= (SureUpDistance + 6))//!!
							{
								liftandcarryinfo->BodyState = Up;
								liftandcarryinfo->UpFlag = true;
								liftandcarryinfo->StrategyState = CatchTop;
							}
							else
							{
								if (liftandcarryinfo->LeftCenterFootDistance <= SureUpDistance && liftandcarryinfo->RightCenterFootDistance <= SureUpDistance)//11
								{
									if (liftandcarryinfo->LeftFootDistance > (SureUpDistance + 10) && liftandcarryinfo->RightFootDistance <= (SureUpDistance + 10))
									{
										liftandcarryinfo->BodyState = RightShift;
									}
									else if (liftandcarryinfo->LeftFootDistance <= (SureUpDistance + 10) && liftandcarryinfo->RightFootDistance > (SureUpDistance + 10))
									{

										liftandcarryinfo->BodyState = LeftShift;
									}
									else if (liftandcarryinfo->LeftFootDistance <= (SureUpDistance + 11) && liftandcarryinfo->RightFootDistance <= (SureUpDistance + 11))
									{
										liftandcarryinfo->BodyState = Up;
										liftandcarryinfo->UpFlag = true;
										liftandcarryinfo->StrategyState = CatchTop;
									}
								}
								else if (liftandcarryinfo->LeftCenterFootDistance > SureUpDistance && liftandcarryinfo->RightCenterFootDistance <= SureUpDistance)//01
								{
									liftandcarryinfo->BodyState = SmallRightRotation;//新增左右璇會前進一點;
								}
								else if (liftandcarryinfo->LeftCenterFootDistance <= SureUpDistance && liftandcarryinfo->RightCenterFootDistance > SureUpDistance)//10
								{
									liftandcarryinfo->BodyState = SmallLeftRotation;
								}
								else
								{
									liftandcarryinfo->BodyState = SmallFront;
								}
							}
						}
						else if ((liftandcarryinfo->LeftFootDistance <= SureUpDistance) && (liftandcarryinfo->CenterFootDistance > SureUpDistance) && (liftandcarryinfo->RightFootDistance > SureUpDistance))		//100
						{
							if ((liftandcarryinfo->RightFootDistance - liftandcarryinfo->CenterFootDistance > 16)||((liftandcarryinfo->CenterFootDistance > SureUpDistance + 12)))//30度  && (liftandcarryinfo->RightFootDistance > SureUpDistance + 15)
							{
								liftandcarryinfo->BodyState = BigLeftRotation;
							}
							else if(liftandcarryinfo->RightFootDistance - liftandcarryinfo->CenterFootDistance > 6)//15度
							{
								liftandcarryinfo->BodyState = SmallLeftRotation;
							}
							else
							{
								if (liftandcarryinfo->CenterFootDistance - liftandcarryinfo->LeftFootDistance > 15 && liftandcarryinfo->RightFootDistance - liftandcarryinfo->LeftFootDistance > 30)
								{
									liftandcarryinfo->BodyState = BigLeftRotation;
								}
								else if (liftandcarryinfo->CenterFootDistance - liftandcarryinfo->LeftFootDistance > 6 && liftandcarryinfo->RightFootDistance - liftandcarryinfo->LeftFootDistance > 12)
								{
									liftandcarryinfo->BodyState = SmallLeftRotation;
								}
								else
								{
									liftandcarryinfo->BodyState = SmallFront;
								}
							}
						}
						else
						{
							liftandcarryinfo->BodyState = Walk2Step;
						}
						//up end
					}
					else if(liftandcarryinfo->DangerLeftFlag && !liftandcarryinfo->DangerRightFlag)
					{
						liftandcarryinfo->BodyState = RightShift;
					}
					else if(!liftandcarryinfo->DangerLeftFlag && liftandcarryinfo->DangerRightFlag)
					{
						liftandcarryinfo->BodyState = LeftShift;
					}
					else if(liftandcarryinfo->DangerLeftFlag && liftandcarryinfo->DangerRightFlag)
					{
						if(liftandcarryinfo->DangerLeftDistance <= liftandcarryinfo->DangerRightDistance)
						{
							liftandcarryinfo->BodyState = BigLeftRotation;
						}
						else
						{
							liftandcarryinfo->BodyState = BigRightRotation;
						}
					}
				}
				else		//down
				{
					if(!liftandcarryinfo->DangerLeftFlag && !liftandcarryinfo->DangerRightFlag)
					{
						if ((liftandcarryinfo->LeftFootDistance <= SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->CenterFootDistance <= SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->RightFootDistance <= SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->LeftCenterFootDistance <= SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->RightCenterFootDistance <= SureUpDistance + ErrorDownDistance))
						{
							liftandcarryinfo->BodyState = Up;
							//liftandcarryinfo->DownFlag = true;
							liftandcarryinfo->StrategyState = DecideDownDistance;
						}
						else if ((liftandcarryinfo->LeftFootDistance > SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->CenterFootDistance <= SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->RightFootDistance <= SureUpDistance + ErrorDownDistance))		//011
						{
							if (liftandcarryinfo->LeftFootDistance <= SureUpDistance + ErrorDownDistance + 5 + LeftFootError)
							{
								liftandcarryinfo->BodyState = Up;
								//liftandcarryinfo->DownFlag = true;
								liftandcarryinfo->StrategyState = DecideDownDistance;
							}
							else
							{
								liftandcarryinfo->BodyState = SmallRightRotation;
							}
						}
						else if ((liftandcarryinfo->LeftFootDistance <= SureUpDistance + ErrorDownDistance + LeftFootError) && (liftandcarryinfo->CenterFootDistance > SureUpDistance) && (liftandcarryinfo->RightFootDistance <= SureUpDistance + ErrorDownDistance))		//101
						{
							 if (liftandcarryinfo->CenterFootDistance <= (SureUpDistance + ErrorDownDistance + 5) && liftandcarryinfo->LeftCenterFootDistance <= (SureUpDistance + ErrorDownDistance) && liftandcarryinfo->RightCenterFootDistance <=(SureUpDistance + ErrorDownDistance))
							{
								liftandcarryinfo->BodyState = Up;
								//liftandcarryinfo->DownFlag = true;
								liftandcarryinfo->StrategyState = DecideDownDistance;
							}
							else
							{
								liftandcarryinfo->BodyState = SmallFront;
							}
						}
						else if ((liftandcarryinfo->LeftFootDistance > SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->CenterFootDistance > SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->RightFootDistance <= SureUpDistance + ErrorDownDistance))		//001
						{
							if (abs(liftandcarryinfo->LeftFootDistance - liftandcarryinfo->CenterFootDistance > 16))//30度  ||(liftandcarryinfo->CenterFootDistance > SureUpDistance + 12)
							{
								liftandcarryinfo->BodyState = BigRightRotation;//試試看絕對值
							}
							else if(abs(liftandcarryinfo->LeftFootDistance - liftandcarryinfo->CenterFootDistance > 6))//15度
							{
								liftandcarryinfo->BodyState = SmallRightRotation;
							}
							else
							{
								if ((liftandcarryinfo->RightFootDistance > SureUpDistance + ErrorDownDistance - 4))//&& liftandcarryinfo->SecStair == Stair_3
								{
									liftandcarryinfo->BodyState = SmallFront;//temp change
								}
								//else if ((liftandcarryinfo->RightFootDistance > SureUpDistance + ErrorDownDistance - 8))//&& liftandcarryinfo->SecStair == Stair_3
								//{
								//liftandcarryinfo->BodyState = SuperSmallFront;
								//}
								else// && abs(liftandcarryinfo->CenterFootDistance - liftandcarryinfo->RightFootDistance <= 5)
								{
									liftandcarryinfo->BodyState = SmallLeftShift;//SureUpDistance至少25才判斷的到
								}
							}
						}
						else if ((liftandcarryinfo->LeftFootDistance <= SureUpDistance + ErrorDownDistance + LeftFootError) && (liftandcarryinfo->CenterFootDistance <= SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->RightFootDistance > SureUpDistance + ErrorDownDistance))		//110
						{
							if (liftandcarryinfo->RightFootDistance <= SureUpDistance + ErrorDownDistance + 5)
							{
								liftandcarryinfo->BodyState = Up;
								//liftandcarryinfo->DownFlag = true;
								liftandcarryinfo->StrategyState = DecideDownDistance;
							}
							else
							{
								liftandcarryinfo->BodyState = SmallLeftRotation;
							}
						}
						else if ((liftandcarryinfo->LeftFootDistance > SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->CenterFootDistance <= SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->RightFootDistance > SureUpDistance + ErrorDownDistance))		//010
						{
							liftandcarryinfo->BodyState = SmallFront;
						}
						else if ((liftandcarryinfo->LeftFootDistance <= SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->CenterFootDistance > SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->RightFootDistance > SureUpDistance + ErrorDownDistance))		//100
						{			
							if (abs(liftandcarryinfo->RightFootDistance - liftandcarryinfo->CenterFootDistance > 16 ))//30度 此為坡浪型邊界修正，下坡因該不需要 || (liftandcarryinfo->CenterFootDistance > SureUpDistance + 12)
							{
								liftandcarryinfo->BodyState = BigLeftRotation;
							}
							else if(abs(liftandcarryinfo->RightFootDistance - liftandcarryinfo->CenterFootDistance > 6))//15度
							{
								liftandcarryinfo->BodyState = SmallLeftRotation;
							}
							else
							{
								if ((liftandcarryinfo->LeftFootDistance > SureUpDistance + ErrorDownDistance - 4))//&& liftandcarryinfo->SecStair == Stair_3
								{
									liftandcarryinfo->BodyState = SmallFront;
								}
								//else if ((liftandcarryinfo->LeftFootDistance > SureUpDistance + ErrorDownDistance - 8))//&& liftandcarryinfo->SecStair == Stair_3
								//{
								//liftandcarryinfo->BodyState = SuperSmallFront;
								//}
								else// && abs(liftandcarryinfo->CenterFootDistance - liftandcarryinfo->RightFootDistance <= 5)
								{
									liftandcarryinfo->BodyState = SmallRightShift;//SureUpDistance至少25才判斷的到
								}
							}
						}
						else if ((liftandcarryinfo->LeftFootDistance > 60) && (liftandcarryinfo->CenterFootDistance > 60) && (liftandcarryinfo->RightFootDistance > 60))
						{
							liftandcarryinfo->BodyState = Spr;
						}
						else if ((liftandcarryinfo->LeftFootDistance > 40) && (liftandcarryinfo->CenterFootDistance > 40) && (liftandcarryinfo->RightFootDistance > 40))//000
						{
							liftandcarryinfo->BodyState = BigFront;//大直走
						}
						else if ((liftandcarryinfo->LeftFootDistance > SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->CenterFootDistance > SureUpDistance + ErrorDownDistance) && (liftandcarryinfo->RightFootDistance > SureUpDistance + ErrorDownDistance))//000
						{
							liftandcarryinfo->BodyState = SmallFront;//小直走
						}
					}
					else if(liftandcarryinfo->DangerLeftFlag && !liftandcarryinfo->DangerRightFlag)
					{
						liftandcarryinfo->BodyState = RightShift;
					}
					else if(!liftandcarryinfo->DangerLeftFlag && liftandcarryinfo->DangerRightFlag)
					{
						liftandcarryinfo->BodyState = LeftShift;
					}
					else if(liftandcarryinfo->DangerLeftFlag && liftandcarryinfo->DangerRightFlag)
					{
						if(liftandcarryinfo->DangerLeftDistance <= liftandcarryinfo->DangerRightDistance)
						{
							liftandcarryinfo->BodyState = BigLeftRotation;
						}
						else
						{
							liftandcarryinfo->BodyState = BigRightRotation;
						}
					}
				}
			}
			else if (!liftandcarryinfo->LeftSlopeFlag && !liftandcarryinfo->CenterSlopeFlag && !liftandcarryinfo->RightSlopeFlag)//000
			{
				if(liftandcarryinfo->LeftFindWoodFlag && !liftandcarryinfo->RightFindWoodFlag && liftandcarryinfo->RobotUp)
				{
					liftandcarryinfo->BodyState = BigLeftRotation;	
				}else if(!liftandcarryinfo->LeftFindWoodFlag && liftandcarryinfo->RightFindWoodFlag && liftandcarryinfo->RobotUp)
				{
					liftandcarryinfo->BodyState = BigRightRotation;
				}else{
					liftandcarryinfo->BodyState = Spr;
				}
			}
			else if (!liftandcarryinfo->LeftSlopeFlag && liftandcarryinfo->CenterSlopeFlag && !liftandcarryinfo->RightSlopeFlag)//010
			{
				if (liftandcarryinfo->CenterFootDistance >= SureUpDistance + 20)
				{
					liftandcarryinfo->BodyState = BigFront;
				}
				else
				{
					liftandcarryinfo->BodyState = SmallFront;//小直走
				}
			}
			else if(liftandcarryinfo->LeftSlopeFlag && liftandcarryinfo->CenterSlopeFlag && !liftandcarryinfo->RightSlopeFlag)//110
			{
				if (liftandcarryinfo->RobotUp)
				{
					if (liftandcarryinfo->CenterFootDistance > SureUpDistance + 25 && liftandcarryinfo->LeftFootDistance > SureUpDistance + 25)
					{
						liftandcarryinfo->BodyState = BigFront;
					}
					else if (liftandcarryinfo->CenterFootDistance > SureUpDistance + 15 && liftandcarryinfo->LeftFootDistance > SureUpDistance + 15)
					{
						liftandcarryinfo->BodyState = SmallFront;
					}
					else if ((liftandcarryinfo->CenterFootDistance - liftandcarryinfo->LeftFootDistance) > 15)
					{
						liftandcarryinfo->BodyState = BigLeftRotation;
					}
					else if ((liftandcarryinfo->CenterFootDistance - liftandcarryinfo->LeftFootDistance) > 6)
					{
						liftandcarryinfo->BodyState = SmallLeftRotation;
					}
					else
					{
						liftandcarryinfo->BodyState = LeftShift;
					}
				}
				else
				{
					if (liftandcarryinfo->CenterFootDistance > 60 && liftandcarryinfo->LeftFootDistance > 60)
					{
						liftandcarryinfo->BodyState = Spr;
					}
					else if (liftandcarryinfo->CenterFootDistance > SureUpDistance + 20 && liftandcarryinfo->LeftFootDistance > SureUpDistance + 20)
					{
						liftandcarryinfo->BodyState = BigFront;
					}
					else if (liftandcarryinfo->CenterFootDistance > SureUpDistance + 10 && liftandcarryinfo->LeftFootDistance > SureUpDistance + 10)
					{
						liftandcarryinfo->BodyState = SmallFront;
					}
					else if ((liftandcarryinfo->CenterFootDistance - liftandcarryinfo->LeftFootDistance) > 10)
					{
						liftandcarryinfo->BodyState = BigLeftRotation;
					}
					else
					{
						liftandcarryinfo->BodyState = LeftShift;//應該是還好...
					}

				}
			}
			else if(!liftandcarryinfo->LeftSlopeFlag && liftandcarryinfo->CenterSlopeFlag && liftandcarryinfo->RightSlopeFlag)//011
			{
				if (liftandcarryinfo->RobotUp)
				{
					if (liftandcarryinfo->CenterFootDistance > SureUpDistance + 25 && liftandcarryinfo->RightFootDistance > SureUpDistance + 25)
					{
						liftandcarryinfo->BodyState = BigFront;
					}
					else if (liftandcarryinfo->CenterFootDistance > SureUpDistance + 15 && liftandcarryinfo->RightFootDistance > SureUpDistance + 15)//因為平移才+15距離
					{
						liftandcarryinfo->BodyState = SmallFront;
					}
					else if ((liftandcarryinfo->CenterFootDistance - liftandcarryinfo->RightFootDistance) > 15)
					{
						liftandcarryinfo->BodyState = BigRightRotation;
					}
					else if ((liftandcarryinfo->CenterFootDistance - liftandcarryinfo->RightFootDistance) > 6)
					{
						liftandcarryinfo->BodyState = SmallRightRotation;
					}
					else
					{
						liftandcarryinfo->BodyState = RightShift;
					}
				}
				else
				{
					if (liftandcarryinfo->CenterFootDistance > 60 && liftandcarryinfo->RightFootDistance > 60)
					{
						liftandcarryinfo->BodyState = Spr;
					}
					else if (liftandcarryinfo->CenterFootDistance > SureUpDistance + 20 && liftandcarryinfo->RightFootDistance > SureUpDistance + 20)
					{
						liftandcarryinfo->BodyState = BigFront;
					}
					else if (liftandcarryinfo->CenterFootDistance > SureUpDistance + 10 && liftandcarryinfo->RightFootDistance > SureUpDistance + 10)
					{
						liftandcarryinfo->BodyState = SmallFront;
					}
					else if ((liftandcarryinfo->CenterFootDistance - liftandcarryinfo->RightFootDistance) > 10)
					{
						liftandcarryinfo->BodyState = BigRightRotation;
					}
					else
					{
						liftandcarryinfo->BodyState = RightShift;//應該是還好...r
					}
				}
			}
			else if (liftandcarryinfo->LeftSlopeFlag && !liftandcarryinfo->CenterSlopeFlag &&!liftandcarryinfo->RightSlopeFlag)//100
			{
				if (liftandcarryinfo->RobotUp)
				{
					if (liftandcarryinfo->LeftFootDistance > SureUpDistance + 25 && liftandcarryinfo->LeftCenterFootDistance > SureUpDistance + 25)
					{
						liftandcarryinfo->BodyState = BigFront;
					}
					else if (liftandcarryinfo->LeftFootDistance > SureUpDistance + 15 && liftandcarryinfo->LeftCenterFootDistance > SureUpDistance + 15)
					{
						liftandcarryinfo->BodyState = SmallFront;//大左旋
					}
					else if (LeftSlope2 > 0.8)//++++++++++++
					{
						liftandcarryinfo->BodyState = BigLeftRotation;
					}
					else
					{
						liftandcarryinfo->BodyState = LeftShift;
					}
				}
				else
				{
					if (liftandcarryinfo->LeftFootDistance <= SureUpDistance + ErrorDownDistance )
					{
						liftandcarryinfo->BodyState = BigLeftRotation;//大左旋  //temp change  originaly BigRightRotation to prevent leftdanger 
						liftandcarryinfo->StrategyState = DecideDownDistance;
					}
					else if (liftandcarryinfo->LeftFootDistance <= SureUpDistance + 12 + ErrorDownDistance )
					{
						liftandcarryinfo->BodyState = SmallFront;
					}
					else
					{
						liftandcarryinfo->BodyState = SmallLeftRotation;//小右旋 //temp change
					}
				}
			}
			else if (!liftandcarryinfo->LeftSlopeFlag  && !liftandcarryinfo->CenterSlopeFlag && liftandcarryinfo->RightSlopeFlag)//001
			{
				if (liftandcarryinfo->RobotUp)
				{
					if (liftandcarryinfo->RightFootDistance > SureUpDistance + 25 && liftandcarryinfo->RightCenterFootDistance > SureUpDistance + 25)
					{
						liftandcarryinfo->BodyState = BigFront;
					}
					else if (liftandcarryinfo->RightFootDistance > SureUpDistance + 15 && liftandcarryinfo->RightCenterFootDistance > SureUpDistance + 15)
					{
						liftandcarryinfo->BodyState = SmallFront;//大左旋
					}
					else if (RightSlope2 < -0.8)
					{
						liftandcarryinfo->BodyState = BigRightRotation;
					}
					else
					{
						liftandcarryinfo->BodyState = RightShift;
					}
				}
				else
				{
					if(liftandcarryinfo->RightFootDistance  <= SureUpDistance + ErrorDownDistance)
					{
						liftandcarryinfo->BodyState = BigRightRotation;//大右旋   //temp change // originaly BigLeftRotation to prevent Rightdanger
						liftandcarryinfo->StrategyState = DecideDownDistance;
					}
					else if (liftandcarryinfo->RightFootDistance <= SureUpDistance + 12 + ErrorDownDistance)
					{
						liftandcarryinfo->BodyState = SmallFront;
					}
					else
					{
						liftandcarryinfo->BodyState = SmallRightRotation;//小右旋  //temp change
					}
				}
			}
			else if (liftandcarryinfo->LeftSlopeFlag  && !liftandcarryinfo->CenterSlopeFlag && liftandcarryinfo->RightSlopeFlag) //101
			{
				if (liftandcarryinfo->RobotUp)
				{
					if (liftandcarryinfo->LeftFootDistance <= (SureUpDistance-10) && liftandcarryinfo->RightFootDistance <= (SureUpDistance-10))
					{
						liftandcarryinfo->BodyState = Up;
						//liftandcarryinfo->UpFlag = true;
						liftandcarryinfo->StrategyState = CatchTop;
					}
					else
					{
						liftandcarryinfo->BodyState = SmallFront;
					}
				}
				else
				{
					if ((liftandcarryinfo->LeftFootDistance <= SureUpDistance + 10) && (liftandcarryinfo->RightFootDistance <= SureUpDistance +10) && (liftandcarryinfo->RightFootDistance>=liftandcarryinfo->LeftFootDistance))
					{
						liftandcarryinfo->BodyState = BigRightRotation;
					}
					else if ((liftandcarryinfo->LeftFootDistance <= SureUpDistance + 10) && (liftandcarryinfo->RightFootDistance <= SureUpDistance +10) && (liftandcarryinfo->RightFootDistance<=liftandcarryinfo->LeftFootDistance))
					{
						liftandcarryinfo->BodyState = BigLeftRotation;
					}
					else if ((liftandcarryinfo->LeftFootDistance <= SureUpDistance + 5) && (liftandcarryinfo->RightFootDistance > SureUpDistance + 20))
					{
						liftandcarryinfo->BodyState = BigRightRotation;
					}
					else if ((liftandcarryinfo->LeftFootDistance > SureUpDistance + 20) && (liftandcarryinfo->RightFootDistance <= SureUpDistance + 5))//如果有很深的波浪要注意這裡!!!+5拿掉
					{
						liftandcarryinfo->BodyState = BigLeftRotation;
					}
					else
					{
						liftandcarryinfo->BodyState = SmallFront;
					}
				}
				//下波暫時不寫不大可能
			}
			break;
		case DecideDownDistance:
			//tool->Delay(2000);
			if(liftandcarryinfo->ablebodystrategy)	//error
				//if (liftandcarryinfo->FindNextStair)
				//if(!liftandcarryinfo->OnsStepFlag)
			{
				liftandcarryinfo->OnsStepFlag = false;
				{
					liftandcarryinfo->FindNextStair = false;
					/*if (liftandcarryinfo->NextStairDistance > 200)//所以至多走到185
					{
					liftandcarryinfo->CloseY = 5000;	//14500
					}
					else if (liftandcarryinfo->NextStairDistance > 185)//直接取中間值
					{
					liftandcarryinfo->CloseY = 5000;	//13500
					}
					else if (liftandcarryinfo->NextStairDistance > 170)//所以至多走到155
					{
					liftandcarryinfo->CloseY = 5000;	//12100
					}
					else if (liftandcarryinfo->NextStairDistance > 155)//直接取中間值
					{
					liftandcarryinfo->CloseY = 5000;	//10600
					}
					else if (liftandcarryinfo->NextStairDistance > 140)//所以至多走到125
					{
					liftandcarryinfo->CloseY = 4000;	//9800
					}
					else if (liftandcarryinfo->NextStairDistance > 125)//直接取中間值
					{
					liftandcarryinfo->CloseY = 4000;	//8300
					}
					else if (liftandcarryinfo->NextStairDistance > 110)//所以至多走到95
					{
					liftandcarryinfo->CloseY = 4000;	//6900
					}
					else if (liftandcarryinfo->NextStairDistance > 95)//直接取中間值
					{
					liftandcarryinfo->CloseY = 4000;	//5500
					}
					else if (liftandcarryinfo->NextStairDistance > 0)
					{*/
					//tool->Delay(2000);
					liftandcarryinfo->StrategyState = CalSlope;
					return ;
					/*}
					else
					{
					return ;
					}*/
				}
				//else
				{
					//liftandcarryinfo->StrategyState = CalSlope;//20161125
					//liftandcarryinfo->CloseY = 11500;//一個畫面的距離(所以至多走到185)
				}
				//liftandcarryinfo->BodyState = OnsStep;
				//liftandcarryinfo->ablebodystrategy = false;
			}
			break;
		case Finish:
			tool->Delay(4000);
			break;
		}
	}
}

void KidsizeStrategy::Loadparameter()
{
	fstream fin;
	char path[200];
	strcpy(path, PATH.c_str());
	strcat(path, "/SpartanRace_Parameter.ini");
	string sTmp;
	char line[100];
	fin.open(path, ios::in);
	try
	{
		st0_SmallFrontX = tool->readvalue(fin, "st0_SmallFrontX", 1);
		st0_SmallFrontY = tool->readvalue(fin, "st0_SmallFrontY", 1);
		st0_SmallFrontTha = tool->readvalue(fin, "st0_SmallFrontTha", 1);
		st0_SmallFrontimu = tool->readvalue(fin, "st0_SmallFrontimu", 1);

		st0_BigFrontX = tool->readvalue(fin, "st0_BigFrontX", 1);
		st0_BigFrontY = tool->readvalue(fin, "st0_BigFrontY", 1);
		st0_BigFrontTha = tool->readvalue(fin, "st0_BigFrontTha", 1);
		st0_BigFrontimu = tool->readvalue(fin, "st0_BigFrontimu", 1);

		st0_SprX = tool->readvalue(fin, "st0_SprX", 1);
		st0_SprY = tool->readvalue(fin, "st0_SprY", 1);
		st0_SprTha = tool->readvalue(fin, "st0_SprTha", 1);
		st0_Sprimu = tool->readvalue(fin, "st0_Sprimu", 1);

		SuperSmallFrontX = tool->readvalue(fin, "SuperSmallFrontX", 1);
		SuperSmallFrontY = tool->readvalue(fin, "SuperSmallFrontY", 1);
		SuperSmallFrontTha = tool->readvalue(fin, "SuperSmallFrontTha", 1);

		SmallFrontX = tool->readvalue(fin, "SmallFrontX", 1);
		SmallFrontY = tool->readvalue(fin, "SmallFrontY", 1);
		SmallFrontTha = tool->readvalue(fin, "SmallFrontTha", 1);
		SmallFrontimu = tool->readvalue(fin, "SmallFrontimu", 1);
		SmallFrontDelay = tool->readvalue(fin, "SmallFrontDelay", 1);

		BigFrontX = tool->readvalue(fin, "BigFrontX", 1);
		BigFrontY = tool->readvalue(fin, "BigFrontY", 1);
		BigFrontTha = tool->readvalue(fin, "BigFrontTha", 1);
		BigFrontimu = tool->readvalue(fin, "BigFrontimu", 1);
		BigFrontDelay = tool->readvalue(fin, "BigFrontDelay", 1);

		SprX = tool->readvalue(fin, "SprX", 1);
		SprY = tool->readvalue(fin, "SprY", 1);
		SprTha = tool->readvalue(fin, "SprTha", 1);
		Sprimu = tool->readvalue(fin, "Sprimu", 1);
		SprDelay = tool->readvalue(fin, "SprDelay", 1);
		
		LeftShiftX = tool->readvalue(fin, "LeftShiftX", 1);
		LeftShiftY = tool->readvalue(fin, "LeftShiftY", 1);
		LeftShiftTha = tool->readvalue(fin, "LeftShiftTha", 1);
		LeftShiftimu = tool->readvalue(fin, "LeftShiftimu", 1);
		LeftShiftDelay = tool->readvalue(fin, "LeftShiftDelay", 1);

		RightShiftX = tool->readvalue(fin, "RightShiftX", 1);
		RightShiftY = tool->readvalue(fin, "RightShiftY", 1);
		RightShiftTha = tool->readvalue(fin, "RightShiftTha", 1);
		RightShiftimu = tool->readvalue(fin, "RightShiftimu", 1);
		RightShiftDelay = tool->readvalue(fin, "RightShiftDelay", 1);

		SmallLeftShiftX = tool->readvalue(fin, "SmallLeftShiftX", 1);
		SmallLeftShiftY = tool->readvalue(fin, "SmallLeftShiftY", 1);
		SmallLeftShiftTha = tool->readvalue(fin, "SmallLeftShiftTha", 1);
		SmallLeftShiftimu = tool->readvalue(fin, "SmallLeftShiftimu", 1);
		SmallLeftShiftDelay = tool->readvalue(fin, "SmallLeftShiftDelay", 1);

		SmallRightShiftX = tool->readvalue(fin, "SmallRightShiftX", 1);
		SmallRightShiftY = tool->readvalue(fin, "SmallRightShiftY", 1);
		SmallRightShiftTha = tool->readvalue(fin, "SmallRightShiftTha", 1);
		SmallRightShiftimu = tool->readvalue(fin, "SmallRightShiftimu", 1);
		SmallRightShiftDelay = tool->readvalue(fin, "SmallRightShiftDelay", 1);

		SmallLeftRotationX = tool->readvalue(fin, "SmallLeftRotationX", 1);
		SmallLeftRotationY = tool->readvalue(fin, "SmallLeftRotationY", 1);
		SmallLeftRotationTha = tool->readvalue(fin, "SmallLeftRotationTha", 1);
		SmallLeftRotationimu = tool->readvalue(fin, "SmallLeftRotationimu", 1);
		SmallLeftRotationDelay = tool->readvalue(fin, "SmallLeftRotationDelay", 1);
		
		SmallRightRotationX = tool->readvalue(fin, "SmallRightRotationX", 1);
		SmallRightRotationY = tool->readvalue(fin, "SmallRightRotationY", 1);
		SmallRightRotationTha = tool->readvalue(fin, "SmallRightRotationTha", 1);
		SmallRightRotationimu = tool->readvalue(fin, "SmallRightRotationimu", 1);
		SmallRightRotationDelay = tool->readvalue(fin, "SmallRightRotationDelay", 1);

		BigLeftRotationX = tool->readvalue(fin, "BigLeftRotationX", 1);
		BigLeftRotationY = tool->readvalue(fin, "BigLeftRotationY", 1);
		BigLeftRotationTha = tool->readvalue(fin, "BigLeftRotationTha", 1);
		BigLeftRotationimu = tool->readvalue(fin, "BigLeftRotationimu", 1);
		BigLeftRotationDelay = tool->readvalue(fin, "BigLeftRotationDelay", 1);

		BigRightRotationX = tool->readvalue(fin, "BigRightRotationX", 1);
		BigRightRotationY = tool->readvalue(fin, "BigRightRotationY", 1);
		BigRightRotationTha = tool->readvalue(fin, "BigRightRotationTha", 1);
		BigRightRotationimu = tool->readvalue(fin, "BigRightRotationimu", 1);
		BigRightRotationDelay = tool->readvalue(fin, "BigRightRotationDelay", 1);

		Walk2StepX = tool->readvalue(fin, "Walk2StepX", 1);
		Walk2StepY = tool->readvalue(fin, "Walk2StepY", 1);
		Walk2StepTha = tool->readvalue(fin, "Walk2StepTha", 1);
		Walk2Stepimu = tool->readvalue(fin, "Walk2Stepimu", 1);
		Walk2StepDelay = tool->readvalue(fin, "Walk2StepDelay", 1);

		Hole_LeftX = tool->readvalue(fin, "Hole_LeftX", 1);
		Hole_LeftY = tool->readvalue(fin, "Hole_LeftY", 1);
		Hole_LeftTha = tool->readvalue(fin, "Hole_LeftTha", 1);
		Hole_Leftimu = tool->readvalue(fin, "Hole_Leftimu", 1);
		
		Hole_RightX = tool->readvalue(fin, "Hole_RightX", 1);
		Hole_RightY = tool->readvalue(fin, "Hole_RightY", 1);
		Hole_RightTha = tool->readvalue(fin, "Hole_RightTha", 1);
		Hole_Rightimu = tool->readvalue(fin, "Hole_Rightimu", 1);

		Hole_Delay = tool->readvalue(fin, "Hole_Delay", 1);

		LC_StepX = tool->readvalue(fin, "LC_StepX", 1);
		LC_StepY = tool->readvalue(fin, "LC_StepY", 1);
		LC_StepTha = tool->readvalue(fin, "LC_StepTha", 1);
		LC_Stepimu = tool->readvalue(fin, "LC_Stepimu", 1);
		LC_StepDelay = tool->readvalue(fin, "LC_StepDelay", 1);

		LC_DownX = tool->readvalue(fin, "LC_DownX", 1);
		LC_DownY = tool->readvalue(fin, "LC_DownY", 1);
		LC_DownTha = tool->readvalue(fin, "LC_DownTha", 1);
		LC_Downimu = tool->readvalue(fin, "LC_Downimu", 1);
		LC_DownDelay = tool->readvalue(fin, "LC_DownDelay", 1);

		HeadpositionX = tool->readvalue(fin, "HeadpositionX", 1);
		HeadpositionY = tool->readvalue(fin, "HeadpositionY", 1);
		CW_step = tool->readvalue(fin,"CW_step",1);
		CW_top_stair = tool->readvalue(fin, "CW_top_stair", 1);

		CW_small_frontX = tool->readvalue(fin, "CW_small_frontX", 1);
		CW_small_frontTha = tool->readvalue(fin, "CW_small_frontTha", 1);
		CW_big_frontX = tool->readvalue(fin, "CW_big_frontX", 1);
		CW_big_frontTha = tool->readvalue(fin, "CW_big_frontTha", 1);

		CW_first_hand_delay = tool->readvalue(fin, "CW_first_hand_delay", 1);
		CW_first_foot_delay = tool->readvalue(fin, "CW_first_foot_delay", 1);
		CW_hand_delay = tool->readvalue(fin, "CW_hand_delay", 1);
		CW_foot_delay = tool->readvalue(fin, "CW_foot_delay", 1);

		CW_Up_distance = tool->readvalue(fin, "CW_Up_distance", 1);

		liftandcarryinfo->MoveValue[ContinuousMaxValue].X = tool->readvalue(fin, "[ContinuousMaxValue].X", 1); 
    	liftandcarryinfo->MoveValue[ContinuousMaxValue].Y = tool->readvalue(fin, "[ContinuousMaxValue].Y", 1); 
    	liftandcarryinfo->MoveValue[ContinuousMaxValue].Theta = tool->readvalue(fin, "[ContinuousMaxValue].Theta", 1); 
 
   		liftandcarryinfo->MoveValue[ContinuousShift].X = tool->readvalue(fin, "[ContinuousShift].X", 1); 
    	liftandcarryinfo->MoveValue[ContinuousShift].Y = tool->readvalue(fin, "[ContinuousShift].Y", 1); 
    	liftandcarryinfo->MoveValue[ContinuousShift].Theta = tool->readvalue(fin, "[ContinuousShift].Theta", 1); 
 
    	liftandcarryinfo->MoveValue[ContinuousOneStep].X = tool->readvalue(fin, "[ContinuousOneStep].X", 1); 
    	liftandcarryinfo->MoveValue[ContinuousOneStep].Y = tool->readvalue(fin, "[ContinuousOneStep].Y", 1); 
    	liftandcarryinfo->MoveValue[ContinuousOneStep].Theta = tool->readvalue(fin, "[ContinuousOneStep].Theta", 1); 
		CloseContinuousFlag = tool->readvalue(fin, "CloseContinuousFlag", 1); 

		fin.close();
	}
	catch(exception e)
	{
	}
}

void KidsizeStrategy::Strategy_Select()
{
	if(strategyinfo->DIOValue.Switch.D0 == true && strategyinfo->DIOValue.Switch.D1 == false && strategyinfo->DIOValue.Switch.D2 == false)
	{
		liftandcarryinfo->WhichStrategy = strategy_climbingwall;
	}
	else if(strategyinfo->DIOValue.Switch.D0 == false && strategyinfo->DIOValue.Switch.D1 == false && strategyinfo->DIOValue.Switch.D2 == false)
	{
		liftandcarryinfo->Easyflag = true;
		liftandcarryinfo->Normalflag = false;
		liftandcarryinfo->Hardflag = false;
		liftandcarryinfo->WhichStrategy = strategy_liftandcarry;
	}
	else if(strategyinfo->DIOValue.Switch.D0 == false && strategyinfo->DIOValue.Switch.D1 == true && strategyinfo->DIOValue.Switch.D2 == false)
	{
		liftandcarryinfo->Easyflag = false;
		liftandcarryinfo->Normalflag = true;
		liftandcarryinfo->Hardflag = false;
		liftandcarryinfo->WhichStrategy = strategy_liftandcarry;
	}
	else if(strategyinfo->DIOValue.Switch.D0 == false && strategyinfo->DIOValue.Switch.D1 == false && strategyinfo->DIOValue.Switch.D2 == true)
	{
		liftandcarryinfo->Easyflag = false;
		liftandcarryinfo->Normalflag = false;
		liftandcarryinfo->Hardflag = true;
		liftandcarryinfo->WhichStrategy = strategy_liftandcarry;
	}
}

void KidsizeStrategy::ContinuousValseAdd(ContinuousValseStates ContinuousValseState, int Value, int MaxValue) 
{ 
  switch (ContinuousValseState) 
  { 
  case ShiftX: 
    if (liftandcarryinfo->MoveValue[Continuous].X > MaxValue) { 
      liftandcarryinfo->MoveValue[Continuous].X -= Value; 
    } 
    else if (liftandcarryinfo->MoveValue[Continuous].X < MaxValue) { 
      liftandcarryinfo->MoveValue[Continuous].X += Value; 
    } 
    break; 
  case ShiftY: 
    if (liftandcarryinfo->MoveValue[Continuous].Y > MaxValue) { 
      liftandcarryinfo->MoveValue[Continuous].Y -= Value; 
    } 
    else if (liftandcarryinfo->MoveValue[Continuous].Y < MaxValue) { 
      liftandcarryinfo->MoveValue[Continuous].Y += Value; 
    } 
    break; 
  case ShiftTheta: 
    if (liftandcarryinfo->MoveValue[Continuous].Theta > MaxValue) { 
      liftandcarryinfo->MoveValue[Continuous].Theta -= Value; 
    } 
    else if (liftandcarryinfo->MoveValue[Continuous].Theta < MaxValue) { 
      liftandcarryinfo->MoveValue[Continuous].Theta += Value; 
    } 
    break; 
  } 
} 
 
void KidsizeStrategy::BodyAction(BodyActionState BodyActionSelect, int MaxValueX, int MaxValueY, int MaxValueTheta, int DelayTime) 
{ 
    switch (BodyActionSelect) 
    { 
    case ContinuousStart: 
      if (!liftandcarryinfo->ContinuousFlag) { 
        ROS_INFO("ContinuousStart"); 
        liftandcarryinfo->ContinuousFlag = true; 
        SendBodyAuto(0, 0, 0, 0, etContinuousStep,etNone); 
      } 
      break; 
    case ContinuousStop: 
      if (liftandcarryinfo->ContinuousFlag) { 
        ROS_INFO("ContinuousStop"); 
        liftandcarryinfo->ContinuousFlag = false; 
        liftandcarryinfo->MoveValue[Continuous].X = liftandcarryinfo->MoveValue[ContinuousOneStep].X; 
        liftandcarryinfo->MoveValue[Continuous].Y = 0; 
        liftandcarryinfo->MoveValue[Continuous].Theta = 0; 
        SendContinuousValue(liftandcarryinfo->MoveValue[ContinuousOneStep].X, 0, 0, liftandcarryinfo->MoveValue[ContinuousOneStep].Theta,etNone); 
        SendBodyAuto(0, 0, 0, 0, etContinuousStep,etNone); 
        tool->Delay(3000); 
      } 
      break; 
    case Continuous: 
      ROS_INFO("Continuous"); 
      BodyAction(ContinuousStart); 
      if (liftandcarryinfo->ContinuousFlag) { 
        liftandcarryinfo->MoveValue[ContinuousShift].X > 0 ? ContinuousValseAdd(ShiftX, liftandcarryinfo->MoveValue[ContinuousShift].X, MaxValueX) : ContinuousValseAdd(ShiftX, -liftandcarryinfo->MoveValue[ContinuousShift].X, MaxValueX); 
        liftandcarryinfo->MoveValue[ContinuousShift].Y > 0 ? ContinuousValseAdd(ShiftY, liftandcarryinfo->MoveValue[ContinuousShift].Y, MaxValueY) : ContinuousValseAdd(ShiftY, -liftandcarryinfo->MoveValue[ContinuousShift].Y, MaxValueY); 
        liftandcarryinfo->MoveValue[ContinuousShift].Theta > 0 ? ContinuousValseAdd(ShiftTheta, liftandcarryinfo->MoveValue[ContinuousShift].Theta, MaxValueTheta) : ContinuousValseAdd(ShiftTheta, -liftandcarryinfo->MoveValue[ContinuousShift].Theta, MaxValueTheta); 
        SendContinuousValue(liftandcarryinfo->MoveValue[Continuous].X, liftandcarryinfo->MoveValue[Continuous].Y, 0, liftandcarryinfo->MoveValue[Continuous].Theta,etNone); 
      } 
      tool->Delay(DelayTime);
      break; 
    } 
} 



void KidsizeStrategy::strategymain()
{
		if(!isStart)
		{
			if(liftandcarryinfo->WhichStrategy == strategy_liftandcarry)
			{
				liftandcarryinfo->ifinitial = true; //傳給Hole & Foot , 判斷策略指撥是否開啟
				StrategyInitial();

			}
			else if(liftandcarryinfo->WhichStrategy == strategy_climbingwall)
			{
				StrategyInitial();
			}
		}
		else
		{
			if(liftandcarryinfo->WhichStrategy == strategy_liftandcarry)
			{
				gettimeofday(&tend, NULL);
				timeuse = (1000000*(tend.tv_sec - tstart.tv_sec) + (tend.tv_usec - tstart.tv_usec))/1000;
				if(timeuse >= liftandcarryinfo->Delaytime && !liftandcarryinfo->HeadRaiseFlag)
				{
					StrategyBody();
					gettimeofday(&tstart, NULL);
				}
				else if(timeuse >= liftandcarryinfo->HeadDelaytime)
				{
					liftandcarryinfo->HeadRaiseFlag = false;
					StrategyHead();
					//gettimeofday(&tstart, NULL);
				}
				StrategyClassify();
				liftandcarryinfo->InitialFlag = true;
			}
			else if(liftandcarryinfo->WhichStrategy == strategy_climbingwall)
			{
				gettimeofday(&tend, NULL);
				timeuse = (1000000*(tend.tv_sec - tstart.tv_sec) + (tend.tv_usec - tstart.tv_usec))/1000;
				if(timeuse >= liftandcarryinfo->Delaytime)
				{
					CW_StrategyBody();
					gettimeofday(&tstart, NULL);
				}
				CW_StrategyClassify();
				liftandcarryinfo->InitialFlag = true;
			}
		}
		if(liftandcarryinfo->WhichStrategy == strategy_liftandcarry)
		{
			SendmainData(liftandcarryinfo->WhichStair, liftandcarryinfo->HeadPostitionY, liftandcarryinfo->ifinitial, liftandcarryinfo->HeadState, liftandcarryinfo->Hardflag, liftandcarryinfo->Normalflag, liftandcarryinfo->Easyflag);//可能要换其他位置
			//red                                                                                                  //由底算起
			DrawImageFunction(1,etDrawLine,0,320,200,200,255,0,0);  //10
			DrawImageFunction(2,etDrawLine,0,320,190,190,255,0,0);  //20
			DrawImageFunction(3,etDrawLine,0,320,170,170,255,0,0);  //40
			DrawImageFunction(4,etDrawLine,0,320,150,150,255,0,0);  //60

			//virtual foot  (green)
			DrawImageFunction(5,etDrawObject,liftandcarryinfo->LeftFoot.XMin,liftandcarryinfo->LeftFoot.XMax,liftandcarryinfo->LeftFoot.YMin,liftandcarryinfo->LeftFoot.YMax,0,255,0);
			DrawImageFunction(6,etDrawObject,liftandcarryinfo->RightFoot.XMin,liftandcarryinfo->RightFoot.XMax,liftandcarryinfo->RightFoot.YMin,liftandcarryinfo->RightFoot.YMax,0,255,0);
		}
		else if(liftandcarryinfo->WhichStrategy == strategy_climbingwall)
		{
			//DrawImageFunction(15,etDrawHorizontalLine,0,320,liftandcarryinfo->RightFoot.YMax-CW_Slope_Rightdistance,liftandcarryinfo->RightFoot.YMax-CW_Slope_Rightdistance,0,0,255);
			//DrawImageFunction(16,etDrawHorizontalLine,0,320,liftandcarryinfo->LeftFoot.YMax-CW_Slope_Leftdistance,liftandcarryinfo->LeftFoot.YMax-CW_Slope_Leftdistance,0,0,255);
			//...draw something................//
		}
		ShowMainData();	//比賽時建議關閉

}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "kidsize");
	ros::NodeHandle nh;
	KidsizeStrategy kidsizeStrategy(nh);

	ros::Rate loop_rate(30);

	while (nh.ok()) 
	{
		kidsizeStrategy.Loadparameter();
		kidsizeStrategy.Strategy_Select();
		kidsizeStrategy.strategymain();
		ros::spinOnce();
		kidsizeStrategy.Strategy_Select();
		loop_rate.sleep();
	}
	return 0;
}



