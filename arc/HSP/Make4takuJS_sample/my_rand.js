(function()
{
	my_rand_init=[0xD9363228,0x021A79C9,0x7604820B,0xD18E1939];
	ary_seed=[0,0,0,0];
	oiuihiuhiu=0;
	my_rand=
	{
		afadf_Init: function()
		{
			now=new Date();
			today=(now.getYear() * 366 * 31)+(now.getMonth() * 31)+(now.getDate());
			ary_seed[0]=my_rand_init[0]^today;
			ary_seed[1]=my_rand_init[1]^today;
			ary_seed[2]=my_rand_init[2]^today;
			ary_seed[3]=my_rand_init[3]^today;
			oiuihiuhiu=1;
		},
		pppvoi: function()
		{
			afasf_ttoo=ary_seed[0]^(ary_seed[0]<<11);
			ary_seed[0]=ary_seed[1];
			ary_seed[1]=ary_seed[2];
			ary_seed[2]=ary_seed[3];
			ary_seed[3]=(ary_seed[3]^(ary_seed[3]>>19))^(afasf_ttoo^(afasf_ttoo>>8));
			return	ary_seed[3];
		}
	};
}
)();

var	ns_myRand;if(!ns_myRand){
	ns_myRand={};
}

ns_myRand.Init=function(){
	my_rand.afadf_Init();
}

ns_myRand.GetRand=function(){
	return	my_rand.pppvoi();
}
