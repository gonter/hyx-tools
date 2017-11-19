awk gentex01>nedsrc.tex
echo %% function labels>nedsrc01.tex

goto Normal

echo \section{Module Group 03}>>nedsrc.tex
echo \def\LPtopB{Module Group 03}>>nedsrc.tex
awk gentex03 01/ned0131.c>>nedsrc.tex
awk gentex03 01/ned0132.c>>nedsrc.tex
awk gentex03 03/ned0301.c>>nedsrc.tex
awk gentex03 03/ned0302.c>>nedsrc.tex
awk gentex03 03/ned0303.c>>nedsrc.tex
awk gentex03 03/ned0304.c>>nedsrc.tex
awk gentex03 03/ned0305.c>>nedsrc.tex
awk gentex03 03/ned0306.c>>nedsrc.tex
awk gentex03 03/ned0307.c>>nedsrc.tex
awk gentex03 03/ned0308.c>>nedsrc.tex
awk gentex03 03/ned0309.c>>nedsrc.tex
awk gentex03 03/ned0310.c>>nedsrc.tex
awk gentex03 04/ned0423.c>>nedsrc.tex
goto END

:Normal
echo \section{Headers}>>nedsrc.tex
echo \def\LPtopB{Headers}>>nedsrc.tex
awk gentex03 ed.h>>nedsrc.tex
awk gentex03 edhyx.h>>nedsrc.tex
awk gentex03 ned.h>>nedsrc.tex
awk gentex03 message.h>>nedsrc.tex
awk gentex03 proto.h>>nedsrc.tex

echo \section{Main Module}>>nedsrc.tex
awk gentex03 ned00.c>>nedsrc.tex

echo \section{Module Group 00}>>nedsrc.tex
echo \def\LPtopB{Module Group00: Tables and Variables}>>nedsrc.tex
awk gentex03 00/ned0001.c>>nedsrc.tex
awk gentex03 00/ned0001a.c>>nedsrc.tex
awk gentex03 00/ned0001f.c>>nedsrc.tex
awk gentex03 00/ned0001k.c>>nedsrc.tex
awk gentex03 00/ned0001o.c>>nedsrc.tex
awk gentex03 00/ned0001q.c>>nedsrc.tex
awk gentex03 00/ned0001u.c>>nedsrc.tex
awk gentex03 00/ned0001x.c>>nedsrc.tex
awk gentex03 00/ned0002.c>>nedsrc.tex
awk gentex03 00/ned0003.c>>nedsrc.tex
awk gentex03 00/ned0004.c>>nedsrc.tex
awk gentex03 00/ned0005.c>>nedsrc.tex
awk gentex03 00/ned0006.c>>nedsrc.tex
awk gentex03 00/ned0007.c>>nedsrc.tex
awk gentex03 00/ned0008.c>>nedsrc.tex
awk gentex03 00/ned0009.c>>nedsrc.tex
awk gentex03 00/ned0010.c>>nedsrc.tex
awk gentex03 00/ned0011.c>>nedsrc.tex

echo \section{Module Group 01}>>nedsrc.tex
echo \def\LPtopB{Module Group01: Basic Primitives}>>nedsrc.tex
awk gentex03 01/ned0101.c>>nedsrc.tex
awk gentex03 01/ned0102.c>>nedsrc.tex
awk gentex03 01/ned0103.c>>nedsrc.tex
awk gentex03 01/ned0104.c>>nedsrc.tex
awk gentex03 01/ned0105.c>>nedsrc.tex
awk gentex03 01/ned0106.c>>nedsrc.tex
awk gentex03 01/ned0107.c>>nedsrc.tex
awk gentex03 01/ned0108.c>>nedsrc.tex
awk gentex03 01/ned0109.c>>nedsrc.tex
awk gentex03 01/ned0110.c>>nedsrc.tex
awk gentex03 01/ned0111.c>>nedsrc.tex
awk gentex03 01/ned0112.c>>nedsrc.tex
awk gentex03 01/ned0113.c>>nedsrc.tex
awk gentex03 01/ned0114.c>>nedsrc.tex
awk gentex03 01/ned0115.c>>nedsrc.tex
awk gentex03 01/ned0116.c>>nedsrc.tex
awk gentex03 01/ned0117.c>>nedsrc.tex
awk gentex03 01/ned0118.c>>nedsrc.tex
awk gentex03 01/ned0119.c>>nedsrc.tex
awk gentex03 01/ned0120.c>>nedsrc.tex
awk gentex03 01/ned0121.c>>nedsrc.tex
awk gentex03 01/ned0122.c>>nedsrc.tex
awk gentex03 01/ned0123.c>>nedsrc.tex
awk gentex03 01/ned0124.c>>nedsrc.tex
awk gentex03 01/ned0125.c>>nedsrc.tex
awk gentex03 01/ned0126.c>>nedsrc.tex
awk gentex03 01/ned0127.c>>nedsrc.tex
awk gentex03 01/ned0128.c>>nedsrc.tex
awk gentex03 01/ned0129.c>>nedsrc.tex
awk gentex03 01/ned0131.c>>nedsrc.tex
awk gentex03 01/ned0132.c>>nedsrc.tex
awk gentex03 01/ned0133.c>>nedsrc.tex
awk gentex03 01/ned0134.c>>nedsrc.tex
awk gentex03 01/ned0135.c>>nedsrc.tex
awk gentex03 01/ned0136.c>>nedsrc.tex
awk gentex03 01/ned0137.c>>nedsrc.tex
awk gentex03 01/ned0138.c>>nedsrc.tex
awk gentex03 01/ned0139.c>>nedsrc.tex
awk gentex03 01/ned0140.c>>nedsrc.tex
awk gentex03 01/ned0141.c>>nedsrc.tex

echo \section{Module Group 02}>>nedsrc.tex
echo \def\LPtopB{Module Group02: Basic Primitives}>>nedsrc.tex
awk gentex03 02/ned0202.c>>nedsrc.tex
awk gentex03 02/ned0203.c>>nedsrc.tex
awk gentex03 02/ned0204.c>>nedsrc.tex
awk gentex03 02/ned0205.c>>nedsrc.tex
awk gentex03 02/ned0206.c>>nedsrc.tex
awk gentex03 02/ned0207.c>>nedsrc.tex
awk gentex03 02/ned0208.c>>nedsrc.tex
awk gentex03 02/ned0209.c>>nedsrc.tex
awk gentex03 02/ned0210.c>>nedsrc.tex
awk gentex03 02/ned0211.c>>nedsrc.tex
awk gentex03 02/ned0212.c>>nedsrc.tex
awk gentex03 02/ned0213.c>>nedsrc.tex
awk gentex03 02/ned0214.c>>nedsrc.tex
awk gentex03 02/ned0215.c>>nedsrc.tex
awk gentex03 02/ned0216.c>>nedsrc.tex
awk gentex03 02/ned0217.c>>nedsrc.tex
awk gentex03 02/ned0218.c>>nedsrc.tex
awk gentex03 02/ned0219.c>>nedsrc.tex
awk gentex03 02/ned0220.c>>nedsrc.tex
awk gentex03 02/ned0221.c>>nedsrc.tex
awk gentex03 02/ned0222.c>>nedsrc.tex
awk gentex03 02/ned0223.c>>nedsrc.tex
awk gentex03 02/ned0224.c>>nedsrc.tex
awk gentex03 02/ned0225.c>>nedsrc.tex
awk gentex03 02/ned0226.c>>nedsrc.tex
awk gentex03 02/ned0227.c>>nedsrc.tex
awk gentex03 02/ned0228.c>>nedsrc.tex
awk gentex03 02/ned0229.c>>nedsrc.tex
awk gentex03 02/ned0230.c>>nedsrc.tex
awk gentex03 02/ned0231.c>>nedsrc.tex
awk gentex03 02/ned0232.c>>nedsrc.tex

echo \section{Module Group 03}>>nedsrc.tex
echo \def\LPtopB{Module Group03: Primitives}>>nedsrc.tex
awk gentex03 03/ned0301.c>>nedsrc.tex
awk gentex03 03/ned0302.c>>nedsrc.tex
awk gentex03 03/ned0303.c>>nedsrc.tex
awk gentex03 03/ned0304.c>>nedsrc.tex
awk gentex03 03/ned0305.c>>nedsrc.tex
awk gentex03 03/ned0306.c>>nedsrc.tex
awk gentex03 03/ned0307.c>>nedsrc.tex
awk gentex03 03/ned0308.c>>nedsrc.tex
awk gentex03 03/ned0309.c>>nedsrc.tex
awk gentex03 03/ned0310.c>>nedsrc.tex
awk gentex03 03/ned0311.c>>nedsrc.tex
awk gentex03 03/ned0312.c>>nedsrc.tex
awk gentex03 03/ned0313.c>>nedsrc.tex
awk gentex03 03/ned0314.c>>nedsrc.tex
awk gentex03 03/ned0315.c>>nedsrc.tex
awk gentex03 03/ned0316.c>>nedsrc.tex
awk gentex03 03/ned0317.c>>nedsrc.tex
awk gentex03 03/ned0318.c>>nedsrc.tex
awk gentex03 03/ned0319.c>>nedsrc.tex
awk gentex03 03/ned0320.c>>nedsrc.tex
awk gentex03 03/ned0321.c>>nedsrc.tex
awk gentex03 03/ned0322.c>>nedsrc.tex
awk gentex03 03/ned0323.c>>nedsrc.tex
awk gentex03 03/ned0324.c>>nedsrc.tex
awk gentex03 03/ned0325.c>>nedsrc.tex
awk gentex03 03/ned0326.c>>nedsrc.tex
awk gentex03 03/ned0327.c>>nedsrc.tex
awk gentex03 03/ned0328.c>>nedsrc.tex
awk gentex03 03/ned0329.c>>nedsrc.tex
awk gentex03 03/ned0330.c>>nedsrc.tex
awk gentex03 03/ned0331.c>>nedsrc.tex
awk gentex03 03/ned0332.c>>nedsrc.tex
awk gentex03 03/ned0333.c>>nedsrc.tex

echo \section{Module Group 04: Filehandling}>>nedsrc.tex
echo \def\LPtopB{Module Group04: Filehandling}>>nedsrc.tex
awk gentex03 04/ned0401.c>>nedsrc.tex
awk gentex03 04/ned0402.c>>nedsrc.tex
awk gentex03 04/ned0403.c>>nedsrc.tex
awk gentex03 04/ned0404.c>>nedsrc.tex
awk gentex03 04/ned0405.c>>nedsrc.tex
awk gentex03 04/ned0406.c>>nedsrc.tex
awk gentex03 04/ned0408.c>>nedsrc.tex
awk gentex03 04/ned0409.c>>nedsrc.tex
awk gentex03 04/ned0410.c>>nedsrc.tex
awk gentex03 04/ned0411.c>>nedsrc.tex
awk gentex03 04/ned0412.c>>nedsrc.tex
awk gentex03 04/ned0413.c>>nedsrc.tex
awk gentex03 04/ned0414.c>>nedsrc.tex
awk gentex03 04/ned0415.c>>nedsrc.tex
awk gentex03 04/ned0416.c>>nedsrc.tex
awk gentex03 04/ned0417.c>>nedsrc.tex
awk gentex03 04/ned0418.c>>nedsrc.tex
awk gentex03 04/ned0419.c>>nedsrc.tex
awk gentex03 04/ned0420.c>>nedsrc.tex
awk gentex03 04/ned0421.c>>nedsrc.tex
awk gentex03 04/ned0422.c>>nedsrc.tex
awk gentex03 04/ned0423.c>>nedsrc.tex
awk gentex03 04/ned0424.c>>nedsrc.tex
awk gentex03 04/ned0425.c>>nedsrc.tex
awk gentex03 04/ned0426.c>>nedsrc.tex
awk gentex03 04/ned0427.c>>nedsrc.tex
awk gentex03 04/ned0428.c>>nedsrc.tex
awk gentex03 04/ned0429.c>>nedsrc.tex
awk gentex03 04/ned0430.c>>nedsrc.tex

echo \section{Module Group 05}>>nedsrc.tex
echo \def\LPtopB{Module Group05}>>nedsrc.tex
awk gentex03 05/ned0501.c>>nedsrc.tex
awk gentex03 05/ned0502.c>>nedsrc.tex
awk gentex03 05/ned0503.c>>nedsrc.tex
awk gentex03 05/ned0504.c>>nedsrc.tex
awk gentex03 05/ned0505.c>>nedsrc.tex
awk gentex03 05/ned0506.c>>nedsrc.tex
awk gentex03 05/ned0507.c>>nedsrc.tex
awk gentex03 05/ned0508.c>>nedsrc.tex
awk gentex03 05/ned0509.c>>nedsrc.tex
awk gentex03 05/ned0510.c>>nedsrc.tex
awk gentex03 05/ned0511.c>>nedsrc.tex
awk gentex03 05/ned0512.c>>nedsrc.tex
awk gentex03 05/ned0513.c>>nedsrc.tex
awk gentex03 05/ned0514.c>>nedsrc.tex
awk gentex03 05/ned0515.c>>nedsrc.tex
awk gentex03 05/ned0516.c>>nedsrc.tex
awk gentex03 05/ned0517.c>>nedsrc.tex
awk gentex03 05/ned0518.c>>nedsrc.tex
awk gentex03 05/ned0519.c>>nedsrc.tex
awk gentex03 05/ned0520.c>>nedsrc.tex
awk gentex03 05/ned0521.c>>nedsrc.tex
awk gentex03 05/ned0522.c>>nedsrc.tex

echo \section{Module Group 06}>>nedsrc.tex
echo \def\LPtopB{Module Group06}>>nedsrc.tex
awk gentex03 06/ned0603.c>>nedsrc.tex
awk gentex03 06/ned0604.c>>nedsrc.tex
awk gentex03 06/ned0605.c>>nedsrc.tex
awk gentex03 06/ned0606.c>>nedsrc.tex
awk gentex03 06/ned0607.c>>nedsrc.tex
awk gentex03 06/ned0608.c>>nedsrc.tex
awk gentex03 06/ned0609.c>>nedsrc.tex
awk gentex03 06/ned0610.c>>nedsrc.tex
awk gentex03 06/ned0611.c>>nedsrc.tex
awk gentex03 06/ned0612.c>>nedsrc.tex
awk gentex03 06/ned0613.c>>nedsrc.tex
awk gentex03 06/ned0615.c>>nedsrc.tex
awk gentex03 06/ned0616.c>>nedsrc.tex
awk gentex03 06/ned0617.c>>nedsrc.tex
awk gentex03 06/ned0618.c>>nedsrc.tex
awk gentex03 06/ned0619.c>>nedsrc.tex
awk gentex03 06/ned0620.c>>nedsrc.tex
awk gentex03 06/ned0621.c>>nedsrc.tex
awk gentex03 06/ned0622.c>>nedsrc.tex
awk gentex03 06/ned0623.c>>nedsrc.tex
awk gentex03 06/ned0624.c>>nedsrc.tex
awk gentex03 06/ned0625.c>>nedsrc.tex
awk gentex03 06/ned0626.c>>nedsrc.tex

echo \section{Module Group 07}>>nedsrc.tex
echo \def\LPtopB{Module Group07}>>nedsrc.tex
awk gentex03 07/ned0701.c>>nedsrc.tex
awk gentex03 07/ned0702.c>>nedsrc.tex
awk gentex03 07/ned0703.c>>nedsrc.tex
awk gentex03 07/ned0704.c>>nedsrc.tex
awk gentex03 07/ned0705.c>>nedsrc.tex
awk gentex03 07/ned0706.c>>nedsrc.tex
awk gentex03 07/ned0707.c>>nedsrc.tex
awk gentex03 07/ned0708.c>>nedsrc.tex
awk gentex03 07/ned0709.c>>nedsrc.tex
awk gentex03 07/ned0710.c>>nedsrc.tex
awk gentex03 07/ned0711.c>>nedsrc.tex
awk gentex03 07/ned0712.c>>nedsrc.tex
awk gentex03 07/ned0713.c>>nedsrc.tex
awk gentex03 07/ned0714.c>>nedsrc.tex
awk gentex03 07/ned0715.c>>nedsrc.tex
awk gentex03 07/ned0716.c>>nedsrc.tex
awk gentex03 07/ned0717.c>>nedsrc.tex
awk gentex03 07/ned0718.c>>nedsrc.tex
awk gentex03 07/ned0719.c>>nedsrc.tex
awk gentex03 07/ned0720.c>>nedsrc.tex
awk gentex03 07/ned0721.c>>nedsrc.tex
awk gentex03 07/ned0722.c>>nedsrc.tex
awk gentex03 07/ned0723.c>>nedsrc.tex
awk gentex03 07/ned0724.c>>nedsrc.tex
awk gentex03 07/ned0725.c>>nedsrc.tex
awk gentex03 07/ned0726.c>>nedsrc.tex
awk gentex03 07/ned0727.c>>nedsrc.tex
awk gentex03 07/ned0728.c>>nedsrc.tex
awk gentex03 07/ned0729.c>>nedsrc.tex
awk gentex03 07/ned0730.c>>nedsrc.tex
awk gentex03 07/ned0731a.c>>nedsrc.tex
awk gentex03 07/ned0731p.c>>nedsrc.tex
awk gentex03 07/ned0731w.c>>nedsrc.tex
awk gentex03 07/ned0732.c>>nedsrc.tex
awk gentex03 07/ned0733.c>>nedsrc.tex
awk gentex03 07/ned0734.c>>nedsrc.tex
awk gentex03 07/ned0735.c>>nedsrc.tex
awk gentex03 07/ned0736.c>>nedsrc.tex
awk gentex03 07/ned0737.c>>nedsrc.tex
awk gentex03 07/ned0738.c>>nedsrc.tex
awk gentex03 07/ned0739.c>>nedsrc.tex
awk gentex03 07/ned0740.c>>nedsrc.tex
awk gentex03 07/ned0741.c>>nedsrc.tex
awk gentex03 07/ned0742.c>>nedsrc.tex
awk gentex03 07/ned0743.c>>nedsrc.tex
awk gentex03 07/ned0744.c>>nedsrc.tex
awk gentex03 07/ned0745.c>>nedsrc.tex
awk gentex03 07/ned0746.c>>nedsrc.tex
awk gentex03 07/ned0747.c>>nedsrc.tex
awk gentex03 07/ned0748.c>>nedsrc.tex

echo \section{Module Group 08: Features and Hypertext}>>nedsrc.tex
echo \def\LPtopB{Module Group08: Features and Hypertext}>>nedsrc.tex
awk gentex03 08/ned0803.c>>nedsrc.tex
awk gentex03 08/ned0804.c>>nedsrc.tex
awk gentex03 08/ned0805.c>>nedsrc.tex
awk gentex03 08/ned0806.c>>nedsrc.tex
awk gentex03 08/ned0807.c>>nedsrc.tex
awk gentex03 08/ned0808.c>>nedsrc.tex
awk gentex03 08/ned0809.c>>nedsrc.tex
awk gentex03 08/ned0810.c>>nedsrc.tex
awk gentex03 08/ned0811.c>>nedsrc.tex
awk gentex03 08/ned0812.c>>nedsrc.tex
awk gentex03 08/ned0813.c>>nedsrc.tex
awk gentex03 08/ned0814.c>>nedsrc.tex
awk gentex03 08/ned0821.c>>nedsrc.tex
awk gentex03 08/ned0822.c>>nedsrc.tex
awk gentex03 08/ned0823.c>>nedsrc.tex
awk gentex03 08/ned0824.c>>nedsrc.tex
awk gentex03 08/ned0825.c>>nedsrc.tex
awk gentex03 08/ned0826.c>>nedsrc.tex
awk gentex03 08/ned0827.c>>nedsrc.tex
awk gentex03 08/ned0828.c>>nedsrc.tex
awk gentex03 08/ned0830.c>>nedsrc.tex
awk gentex03 08/ned0831.c>>nedsrc.tex
awk gentex03 08/ned0832.c>>nedsrc.tex
awk gentex03 08/ned0833.c>>nedsrc.tex
awk gentex03 08/ned0834.c>>nedsrc.tex
awk gentex03 08/ned0835.c>>nedsrc.tex
awk gentex03 08/ned0836.c>>nedsrc.tex
awk gentex03 08/ned0837.c>>nedsrc.tex
awk gentex03 08/ned0838.c>>nedsrc.tex
awk gentex03 08/ned0839.c>>nedsrc.tex
awk gentex03 08/ned0840.c>>nedsrc.tex
awk gentex03 08/ned0841.c>>nedsrc.tex
awk gentex03 08/ned0842.c>>nedsrc.tex
awk gentex03 08/ned0843.c>>nedsrc.tex
awk gentex03 08/ned0844.c>>nedsrc.tex
awk gentex03 08/ned0845.c>>nedsrc.tex
awk gentex03 08/ned0846.c>>nedsrc.tex
awk gentex03 08/ned0847.c>>nedsrc.tex
awk gentex03 08/ned0848.c>>nedsrc.tex
awk gentex03 08/ned0849.c>>nedsrc.tex
awk gentex03 08/ned0850.c>>nedsrc.tex
awk gentex03 08/ned0851.c>>nedsrc.tex
awk gentex03 08/ned0852.c>>nedsrc.tex
awk gentex03 08/ned0853.c>>nedsrc.tex
awk gentex03 08/ned0854.c>>nedsrc.tex
awk gentex03 08/ned0855.c>>nedsrc.tex
awk gentex03 08/ned0856.c>>nedsrc.tex
awk gentex03 08/ned0857.c>>nedsrc.tex
awk gentex03 08/ned0858.c>>nedsrc.tex
awk gentex03 08/ned0859.c>>nedsrc.tex
awk gentex03 08/ned0860.c>>nedsrc.tex
awk gentex03 08/ned0861.c>>nedsrc.tex
awk gentex03 08/ned0862.c>>nedsrc.tex
awk gentex03 08/ned0863.c>>nedsrc.tex
awk gentex03 08/ned0864.c>>nedsrc.tex
awk gentex03 08/ned0865.c>>nedsrc.tex
awk gentex03 08/ned0866.c>>nedsrc.tex
awk gentex03 08/ned0867.c>>nedsrc.tex
awk gentex03 08/ned0868.c>>nedsrc.tex
awk gentex03 08/ned0869.c>>nedsrc.tex
awk gentex03 08/ned0870.c>>nedsrc.tex
awk gentex03 08/ned0871.c>>nedsrc.tex
awk gentex03 08/ned0872.c>>nedsrc.tex
awk gentex03 08/ned0873.c>>nedsrc.tex
awk gentex03 08/ned0874.c>>nedsrc.tex
awk gentex03 08/ned0875.c>>nedsrc.tex
awk gentex03 08/ned0876.c>>nedsrc.tex
awk gentex03 08/ned0877.c>>nedsrc.tex
awk gentex03 08/ned0878.c>>nedsrc.tex
awk gentex03 08/ned0879.c>>nedsrc.tex
awk gentex03 08/ned0880.c>>nedsrc.tex
awk gentex03 08/ned0881.c>>nedsrc.tex
awk gentex03 08/ned0882.c>>nedsrc.tex
awk gentex03 08/ned0883.c>>nedsrc.tex

echo \section{Module Group 09}>>nedsrc.tex
echo \def\LPtopB{Module Group09}>>nedsrc.tex
awk gentex03 09/ned0901.c>>nedsrc.tex
awk gentex03 09/ned0902.c>>nedsrc.tex
awk gentex03 09/ned0903.c>>nedsrc.tex
awk gentex03 09/ned0904.c>>nedsrc.tex
awk gentex03 09/ned0905.c>>nedsrc.tex
awk gentex03 09/ned0906.c>>nedsrc.tex
awk gentex03 09/ned0907.c>>nedsrc.tex
awk gentex03 09/ned0908.c>>nedsrc.tex
awk gentex03 09/ned0909.c>>nedsrc.tex
awk gentex03 09/ned0910.c>>nedsrc.tex
awk gentex03 09/ned0911.c>>nedsrc.tex
awk gentex03 09/ned0912.c>>nedsrc.tex
awk gentex03 09/ned0913.c>>nedsrc.tex
awk gentex03 09/ned0914.c>>nedsrc.tex
awk gentex03 09/ned0915.c>>nedsrc.tex
awk gentex03 09/ned0916.c>>nedsrc.tex
awk gentex03 09/ned0917.c>>nedsrc.tex
awk gentex03 09/ned0918.c>>nedsrc.tex
awk gentex03 09/ned0919.c>>nedsrc.tex
awk gentex03 09/ned0921.c>>nedsrc.tex
awk gentex03 09/ned0972.c>>nedsrc.tex
awk gentex03 09/ned0973.c>>nedsrc.tex
awk gentex03 09/ned0974.c>>nedsrc.tex
awk gentex03 09/ned0975.c>>nedsrc.tex
awk gentex03 09/ned0976.c>>nedsrc.tex
awk gentex03 09/ned0977.c>>nedsrc.tex
awk gentex03 09/ned0978.c>>nedsrc.tex
awk gentex03 09/ned0979.c>>nedsrc.tex
awk gentex03 09/ned0980.c>>nedsrc.tex

echo \section{Module Group 10}>>nedsrc.tex
echo \def\LPtopB{Module Group10}>>nedsrc.tex
awk gentex03 10/ned1001.c>>nedsrc.tex
awk gentex03 10/ned1002.c>>nedsrc.tex
awk gentex03 10/ned1003.c>>nedsrc.tex
awk gentex03 10/ned1004.c>>nedsrc.tex
awk gentex03 10/ned1005.c>>nedsrc.tex
awk gentex03 10/ned1006.c>>nedsrc.tex
awk gentex03 10/ned1007.c>>nedsrc.tex
awk gentex03 10/ned1008.c>>nedsrc.tex
awk gentex03 10/ned1009.c>>nedsrc.tex
awk gentex03 10/ned1010.c>>nedsrc.tex
awk gentex03 10/ned1011.c>>nedsrc.tex
awk gentex03 10/ned1012.c>>nedsrc.tex
awk gentex03 10/ned1013.c>>nedsrc.tex
awk gentex03 10/ned1014.c>>nedsrc.tex
awk gentex03 10/ned1015.c>>nedsrc.tex
awk gentex03 10/ned1016.c>>nedsrc.tex

echo \section{Module Group 11}>>nedsrc.tex
echo \def\LPtopB{Module Group11}>>nedsrc.tex
awk gentex03 11/ned1101.c>>nedsrc.tex
awk gentex03 11/ned1102.c>>nedsrc.tex
awk gentex03 11/ned1103.c>>nedsrc.tex
awk gentex03 11/ned1104.c>>nedsrc.tex
awk gentex03 11/ned1105.c>>nedsrc.tex
awk gentex03 11/ned1106.c>>nedsrc.tex
awk gentex03 11/ned1107.c>>nedsrc.tex
awk gentex03 11/ned1108.c>>nedsrc.tex
awk gentex03 11/ned1109.c>>nedsrc.tex

:END
echo \pagebreak[4]>>nedsrc.tex
echo \begin{appendix}>>nedsrc.tex
echo \section{Index}>>nedsrc.tex
echo \def\LPtopB{Index}>>nedsrc.tex
echo \def\LPtopC{~}>>nedsrc.tex
echo \def\LPtopD{~}>>nedsrc.tex
echo \begin{tabbing}>>nedsrc.tex
echo \rule{8cm}{0mm}\=\rule{8cm}{0mm}\= \kill>>nedsrc.tex
echo \input{nedsrc01}>>nedsrc.tex
echo \end{tabbing}>>nedsrc.tex
echo \end{appendix}>>nedsrc.tex
echo \end{document}>>nedsrc.tex

translit -tgentextr.tbl nedsrc.tex
sort <nedsrc01.tex >$1.tex
copy $1.tex nedsrc01.tex
translit -tgentextr.tbl nedsrc01.tex

copy nedsrc*.tex l:
list nedsrc.tex
