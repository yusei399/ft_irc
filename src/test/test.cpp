/*

void channel_test()
{

	ChannelManager chm;

	Client cl1(10, "name1");
	//Channel ch("channel1", cl1);
	chm.join("channel1", cl1);
	Channel& ch = chm.find_must_exist("channel1");
	
	std::cout << chm.exist(ch.get_channel_name()) << std::endl;
	Channel ch2("cha2", cl1);
	std::cout << chm.exist(ch2.get_channel_name()) << std::endl;



	std::cout << "ch---------" << std::endl;
	std::cout << ch << std::endl;
	std::cout << "" << std::endl;

	Client cl2(11, "name2");
	chm.join("channel1", cl2);
	chm.join("channel1____", cl2);

	std::cout << "ch---------" << std::endl;
	std::cout << ch << std::endl;
	std::cout << "" << std::endl;

	Client cl3(12, "name3");
	std::cout << "is_memer" << std::endl;
	std::cout << ch.is_member(cl1) << std::endl;
	std::cout << ch.is_member(cl2) << std::endl;
	std::cout << ch.is_member(cl3) << std::endl;

	std::cout << "is_operator" << std::endl;
	std::cout << ch.is_operator(cl1) << std::endl;
	std::cout << ch.is_operator(cl2) << std::endl;
	std::cout << ch.is_operator(cl3) << std::endl;
	
	chm.try_part("channel1", cl1);
	std::cout << "ch---------" << std::endl;
	std::cout << ch << std::endl;
	std::cout << "" << std::endl;

	chm.try_part("channel1", cl2);
	std::cout << "ch---------" << std::endl;
	std::cout << ch << std::endl;
	std::cout << "" << std::endl;


}
*/