#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "GameManager.hpp"
#include "TitleMenu.h"
#include "StartMenu.h"
//#include <NendModule.h>

#include <stdio.h>

using namespace cocos2d;

HelloWorld::~HelloWorld()
{
    //	if (_targets)
    //	{
    //		_targets->release();
    //		_targets = NULL;
    //	}
    //
    //	if (_projectiles)
    //	{
    //		_projectiles->release();
    //		_projectiles = NULL;
    //	}
    
    // cpp don't need to call super dealloc
    // virtual destructor will do this
}

HelloWorld::HelloWorld()
:_targets(NULL)
,_projectiles(NULL)
,_projectilesDestroyed(0)
{
}

int h_num;

struct settokuList {
    char *choice1;		/* 説得内容	*/
    char *choice2;		/* 説得内容	*/
    char *choice3;		/* 説得内容	*/
    int doujou;		/* 同情があるのか*/
};

struct settsumonList {
    char *setsumon;     /* 設問内容 */
    char *choice1;		/* 説得内容	*/
    char *choice2;		/* 説得内容	*/
    char *choice3;		/* 説得内容	*/
    int doujou;		/* 同情があるのか*/
};

bool first_flg=false;
char* stage[25]={"home", "home", "home", "spring", "spring", "spring", "home", "home", "home", "summer", "summer", "summer", "home", "home", "home", "autumn", "autumn", "autumn", "home", "home", "home", "winter", "winter", "winter", "home"};
char setsumons[200][1000]={
    "ジャムの蓋が空かないときどうすればいい,湯煎,よく振る,念じる" ,
    "ドライクリーニングで落ちる汚れは,油汚れ,泥汚れ,汗" ,
    "シリコン製品が食器洗い機不可の理由は,酸に弱い,セットできない,特になし" ,
    "羽毛布団を洗濯するとどうなる,フワフワになる,縮む,固くなる" ,
    "雑巾を熱湯消毒するとき６０℃のお湯なら何分浸ける,15分,10分,5分" ,
    "シーツにポリエステルが入っているとどうなる,毛玉ができやすい,洗濯できない,臭くなる" ,
    "布製品のカビをとるとき洗剤を間違えるとどうなる,色落ちする,溶ける,なんとかなる" ,
    "洗濯物を部屋干しするときはどこに干すといい,風呂場,玄関,台所" ,
    "風呂場の水垢汚れを落とすには何を使うといい,クエン酸,重曹,石鹸" ,
    "キッチンの油汚れを落とすには何を使うといい,重曹,クエン酸,穀物酢" ,
    "洗濯の時に柔軟剤を入れるタイミングは,すすぎ,洗い,脱水" ,
    "重曹の洗濯に用いる過炭酸ソーダの正式名称は,過炭酸ナトリウム,飽和炭酸ソーダ,過炭素水ソーダ" ,
    "汚水が合併浄化槽に流れる場合に使用する洗剤は何性,中性,酸性,アルカリ性" ,
    "風呂場のカビを防ぐにはどうする,換気,特になし,空気を入れない" ,
    "風呂場の鏡のカルキ汚れを落とすには何を使うと良い,研磨剤入りの洗剤,ザクロ,硝酸入りの洗剤" ,
    "化学繊維100％の靴下を履き続けるとどうなる,臭いが増幅する,ボロボロになる,色落ちする" ,
    "洗濯バサミがたくさんついてる正方形のものの名称は,洗濯ハンガー,方形ハンガー,便利用洗濯バサミ" ,
    "アルコール殺菌での最適なアルコール濃度は,70%,100%,40%" ,
    "低反発の布団を日干しするとどんな弊害がある,特にない,反発しなくなる,成分が溶ける" ,
    "米に湧く蛾を防ぐにはどうする,専用器に入れる,封を締める,紙袋に入れる" ,
    "ウォシュレットノズルを洗うにはどうする,ノズルを引き出す,洗剤を流し込む,手は無い" ,
    "シールの剥がし後のベタベタは何で落とすとよい,アルコール,指でこする,酸性の洗剤" ,
    "ヒメマルカツオブシムシによる害は何,服の穴あき,米に湧く,虫刺され" ,
    "油性マジックの汚れを落とすには何を使うとよい,ミカンの皮,洗剤を刷り込む,ザクロ" ,
    "襟の黄ばみを取る際洗剤を付けて何で擦るとよい,ペットボトルの蓋,ザクロ,石鹸" ,
    "アイロンをかけるには最初に何をする,霧吹き,よく伸ばす,糊をつける" ,
    "革靴を長期保存するときはどうすると臭いにくくなる,新聞紙を入れる,タンスに入れる,植物と保存する" ,
    "誤ってティッシュを一緒に洗濯した時どうすると良い,水に浸す,もう1回洗濯,強く叩く" ,
    "サランラップの切口を見つけるときは何を使うとよい,セロテープ,爪,ペットボトルの蓋" ,
    "金ざるについたデンプンを取るにはどうするとよい,煮沸,塩を振る,乾燥させる" ,
    "畳のサイズは1畳何cm×何cm,90×180,75×145,85×165" ,
    "リネン生地の素材は,麻,綿,動物性繊維" ,
    "カーテンの遮光等級の2級は遮光率何％以上か,99.8%,99.5%,99.3%" ,
    "クーリングオフが適用できる期間は何日以内,8日,11日,12日" ,
    "押入の上部の高い位置にある収納の呼称は,天袋,上端収納,納器" ,
    "テーブルクロスを何色にすると食欲が増進するか,オレンジ,黄緑,紫" ,
    "IHヒーターの発熱方法は,電磁誘導加熱,磁束集約発熱,気化冷凍法" ,
    "洗濯マークの弱40はどんな意味,40℃以下で弱水流,40℃弱まで,40℃前後は不可" ,
    "スプレー缶を捨てる時は何をしないといけない,穴をあける,よく振る,特になし" ,
    "風呂場の排水溝の髪の毛等を塞き止めるものの呼称は,ストレーナ,ストッパ,ストレングス" ,
    "電気温水器の寿命は大体何年,15年,30年,45年" ,
    "冬場の風呂は追い炊きと給湯どちらがよい,給湯,追い炊き,特になし" ,
    "水道水のpHの基準値はいくつ,5.8～8.6,4.6～5.4,7.2～9.8" ,
    "灯油ポンプを発明したのは誰,ドクター中松,ムツゴロウ,ラッシャー板前" ,
    "トイレの詰りを直すスッポンの正式名称は,ラバーカッチ,ラバーカッニ,ラバーカップ" ,
    "テフロン加工のフライパンでやってはいけないことは,空焚き,洗剤で洗う,IHで加熱" ,
    "掃除機の中で排気が一番きれいなのはどれ,サイクロン式,紙パック式,トルネード式" ,
    "靴を洗うとき何を使うと臭いが消えやすい,酸素系漂白剤,酵素系漂白剤,窒素系漂白剤" ,
    "パンツの黄ばみを消すには何入りの石鹸を使うとよい,ケイ酸塩,硝酸ナトリウム,リン酸カルシウム" ,
    "クエン酸と塩素系洗剤を混ぜるとどうなる,塩素ガスが発生,特になし,塩酸が生成" ,
    "アサリの砂抜きをするときの適切な塩分濃度は,4%,8%,16%" ,
    "お米の１合は何グラム,150g,134g,130g" ,
    "計量するときの大さじと小さじはそれぞれ何cc,15ccと5cc,10ccと5cc,20ccと10cc" ,
    "半熟ゆで卵を作るには沸騰したお湯で何分茹でる,4分,7分,10分" ,
    "焼鳥の砂肝は人間で言うとどの部分,胃,肝臓,脾臓" ,
    "アンチョビは何の塩漬け,カタクチイワシ,スケトウダラ,ロウニンアジ" ,
    "ご飯を冷凍保存するときにおいしく食べれる期限は,3か月,6ヵ月,8か月" ,
    "オニオンスライスの辛みを抜く方法は,酢水につける,茹でる,塩を振る" ,
    "ブロッコリーの上のつぶつぶは何,蕾,花,葉" ,
    "魚をグリルで焼くときの適切な時間配分は,表3分：裏7分,表5分：裏5分,表7分：裏3分" ,
    "ベーコンをカリカリに焼くときの火加減は,弱火,強火,中火" ,
    "パプリカの赤、オレンジ、黄で一番栄養素が高いのは,オレンジ,赤,黄" ,
    "煮物を作る時に味がしみ込むタイミングは,火を止めている時,沸騰する前,沸騰中" ,
    "アルミホイルの表と裏の違いは,特にない,表を内側に使用,裏を内側に使用" ,
    "オリーブオイルを冷蔵庫で保存するとどうなる,固まる,栄養価が増える,栄養価が減る" ,
    "この中で生で食べられないのは,ジャガイモ,オクラ,じゅんさい" ,
    "魚を焼くときの適切な火加減は,遠火の強火,近火の弱火,近火の強火" ,
    "新玉ねぎとはいつごろ収穫されたものを指すか,4～5月,6～7月,2～3月" ,
    "山芋が生で食べられるのは何が沢山含まれるためか,アミラーゼ,アミリウム,アミニン" ,
    "ジャガイモを調理する際に取らないといけない部分は,芽,皮,根" ,
    "スーパーの見切り品で椎茸の栄養はどうなっているか,ほぼ変わらない,減少,増加" ,
    "ピータンの原料は何,アヒルの卵,ガチョウの卵,カモの卵" ,
    "干しシイタケは何時間以上かけて戻すか,24時間,8時間,16時間" ,
    "ホールトマトの酸味を抑えるにはどうする,砂糖を入れる,酢を入れる,塩を入れる" ,
    "レバーの臭みを取るには何につける,牛乳,酢,はちみつ" ,
    "タケノコのあく抜きをするときには何を入れる,米ぬか,米麹,ぬか味噌" ,
    "桜肉は何の肉,馬,猪,兎" ,
    "冷ごはんの上手な使い方は,チャーハン,牛丼,ライスバーガー" ,
    "カチカチになったフランスパンの上手な使い方は,フレンチトースト,ハンバーガー,サンドイッチ" ,
    "ホタテを生で食べるときに取る部位の俗称は,ウロ,ウソ,ウノ" ,
    "ニンニクの皮を剥き易くする方法は,レンジでチン,念じる,牛乳につける" ,
    "ペペルンゴの意味は,胡椒少々,～添え,粘着性のソース" ,
    "高野豆腐を冷凍するとどうなる,変わらない,ボソボソになる,栄養価が減る" ,
    "ゆで卵の殻の簡単な剥き方は,冷水で冷やす,沸騰させない,直ぐ剥く" ,
    "料理のさしすせそは調味料の何を意味する,入れる順番,使う量の順番,入手難度の順番" ,
    "ほうれん草を茹でるときに塩を入れる理由は,アク抜き,色見出し,味付け" ,
    "おにぎりの作り方でダメなのは,握る,ご飯を固めに炊く,お椀の中で転がす" ,
    "料理を取り分けたりするための杓子を何という,レードル,シードル,スチードル" ,
    "パンなどの生地を分割するのに使う調理器具は,スケッパー,トリッパー,スキッパー" ,
    "包丁を砥石で研ぐとき１０円玉何枚分浮かせる,3枚,2枚,4枚" ,
    "魚の切り身を冷蔵・冷凍保存するときに必要なことは,シートを取る,直ぐに冷凍する,塩を振る" ,
    "生卵をレンジでチンするとどうなる,爆発する,ゆで卵になる,半熟卵になる" ,
    "うどんを作る時の小麦粉の種類は,強力粉,薄力粉,中力粉" ,
    "カレーを作るとき具材を煮込む前に何をする,炒める,粗熱を取る,水分を拭き取る" ,
    "普通の醤油にもう一回醤油麹を仕込んだ物を何という,刺身醤油,酢醤油,出汁醤油" ,
    "出汁巻き卵をふわっとさせるときの出汁の割合は,出汁6：卵1,出汁3：卵1,出汁1：卵1" ,
    "米を研ぐときは何に入れて研ぐ,ボール,ざる,金ざる" ,
    "クイニーアマンとは何,お菓子,スープ,小鹿のリゾット" ,
    "揚物の油で菜箸全体から勢いよく泡が出る状態は何℃,190℃,220℃,160℃" ,
    "唐揚げを揚げるときの油の温度は,160℃,180℃,200℃" ,
    "遺伝子組み換え食品を食べたときの人体への影響は,特にない,遺伝子障害,嘔吐、下痢" ,
    "病床数がいくつ以上の入院施設を病院と呼ぶか,20,16,11" ,
    "微生物を薬品などを用いて死滅させることを何という,殺菌,消毒,除菌" ,
    "ナッツ類に含まれるオレイン酸は何に効く,高血圧,末端冷え症,貧血" ,
    "乳酸を取り除くには何を食べると良い,梅干し,バナナ,塩辛" ,
    "この中で一番鉄分の多い食品はどれ,あさり,イカ,舞茸" ,
    "この中で一番イボに効くものはどれ,ハトムギ,玄米,月見草" ,
    "ワカメを食べすぎることによる害は,ヨウ素過剰摂取,特になし,毒素蓄積" ,
    "合成サプリと一緒にコーヒーを飲むとどうなる,胃が荒れる,特になし,効果が薄れる" ,
    "水素水を飲むとどういう効果がある,特にない,痩せる,血圧が下がる" ,
    "酵素を壊さない為には味噌汁を何℃以下にする,65℃,85℃,75℃" ,
    "野菜を加熱すると失われる栄養素は,ビタミンC,亜鉛,コラーゲン" ,
    "大豆を食べると血液が何性になる,アルカリ性,中性,酸性" ,
    "手先がつる場合何の不足が考えられる,カリウム,亜鉛,ビタミンK" ,
    "三大栄養素は炭水化物、タンパク質とあと何,脂肪,油脂,オレイン酸" ,
    "青魚に含まれる摂ると頭の良くなる栄養素は,DHA,DHE,DHC" ,
    "痛風の原因になるプリン体を多く含むのは,クロレラ,イクラ,プリン" ,
    "生タマネギを食べると血がどうなる,サラサラ,ドロドロ,コリコリ" ,
    "シャンピニオンエキスはどういう効果がある,消臭,胃のむかつき,火傷" ,
    "トマト等に入っているリコピンの健康作用は,抗酸化,血圧低下,消臭" ,
    "爪がよく割れる場合何を摂取すると良い,亜鉛,鉄分,ビタミンB12" ,
    "茄子の紫色の色素の名前は,ナスニン,アキロール,ニンギス" ,
    "ゴボウに含まれる水溶性食物繊維の名前は,イヌリン,ネコリン,クリリン" ,
    "難消化性デキストリンは何に効く,高血糖,高脂血症,高血圧" ,
    "虫歯の発生を予防する成分は,キシリトール,大豆ペプチド,アルギニン" ,
    "骨芽細胞や砕骨細胞に作用し骨代謝を調節する成分は,乳塩基性ペプチド,硫塩酸化ペプチド,良性拡径ペプチド" ,
    "低分子アルギン酸ナトリウムは何に効果がある,コレステロール値,血糖値,口臭" ,
    "男性のメタボリックシンドロームは腹囲何cm以上,85cm,75cm,80cm" ,
    "かつお節オリゴペプチドは何に効果がある,高血圧,高脂血症,高血糖" ,
    "一定の基準を満たす健康補助食品に許可される表示は,JHFA,特定保健用食品,EPA" ,
    "健康表示を厚生労働大臣が許可した食品を何という,特定保健用食品,特定保健用良品,特定保建用食品" ,
    "大豆イソフラボンを摂取すると何に効果がある,更年期障害,味覚障害,聴覚障害" ,
    "アサイーのポリフェノールはワインの何倍か,10倍,20倍,50倍" ,
    "クエン酸にはどんな効果がある,疲労回復,美肌,消臭" ,
    "中鎖脂肪酸にはどんな効果がある,肥満防止,老化防止,体臭防止" ,
    "グルコサミンを摂取すると何に効く,関節の炎症,骨の炎症,皮膚の炎症" ,
    "ラブレ菌を摂取するとどんな効果がある,感染症予防,虫歯予防,アルツハイマー予防" ,
    "カテキンを摂取するとどんな効果がある,肥満防止,老化防止,体臭防止" ,
    "湯の花を使用するとどんな効果がある,皮膚の引き締め,腋臭軽減,水虫改善" ,
    "カムカムに抗酸化効果があるのは何が入っているから,エラグ酸,ニチル酸,ランツ酸" ,
    "髪のキューティクルが壊れる原因は,紫外線,リンス,PM2.5" ,
    "甲状腺機能を上げるにはどこをマッサージするとよい,鎖骨,眉間,こめかみ" ,
    "コラーゲンを皮膚に塗るとどうなる,保湿効果,吸収される,特になし" ,
    "カフェインの覚醒作用は何時間持続するか,3時間,6時間,1時間" ,
    "睡眠時無呼吸症候群を放置するとどうなる,高血圧,高脂血症,心筋梗塞" ,
    "うつ病になると併せてどういう弊害がある,不眠症,口臭,動脈硬化" ,
    "健康な睡眠時間は何時間か,6時間～8時間,7時間～9時間,5時間～7時間" ,
    "寝る前に入浴する場合の適切なお湯の温度は,ぬるめ,いつも通り,熱め" ,
    "2日間起床を3時間遅らせると体内時計はどうなる,45分遅れる,15分早まる,15分遅れる" ,
    "昼寝は午後の早い時間に何分間するとよいか,30分間,40分間,45分間" ,
    "正月に飲むおとそを漢字で書くと,お屠蘇,お昇祖,お登曾" ,
    "花見が初めて催されたのは何時代,平安時代,室町時代,江戸時代" ,
    "3月下旬から4月上旬にかけて降り続く雨は何という,菜種梅雨,春藤梅雨,桜旬梅雨" ,
    "鯉のぼりを漢字で書くと,鯉幟,鯉登,鯉昇" ,
    "皐月は何月のこと,5月,6月,9月" ,
    "桜餅に使われる葉は何の葉,オオシマサクラ,枝垂桜,ソメイヨシノ" ,
    "除夜の鐘は何回鳴らされる,108,99,708" ,
    "家族揃って鏡開きをするのは何のため,直会,立春,祈祷" ,
    "正月飾りを飾る期間を何というか,松の内,竹の内,梅の内" ,
    "正月飾りを燃やすどんど焼きの別名は,左義長,露払い,施餓鬼" ,
    "正月飾りのしめ飾りにあしらううらじろの意味は,長寿,健康,富" ,
    "年賀状は遅くとも何日までに出す必要があるか,1月7日,1月4日,1月3日" ,
    "御神酒は何と読む,おみき,おみち,おめき" ,
    "喪中の人に年賀状を出したい場合代わりに何を出す,寒中見舞い,喪中見舞い,お歳暮" ,
    "おせちの数の子の意味は,子孫繁栄,学問成就,富" ,
    "おせちの蒲鉾の意味は,日の出,子孫繁栄,学問成就" ,
    "おせちの伊達巻の意味は,学問成就,子孫繁栄,長寿" ,
    "おせちの伍の重を空にするのは何の為,来年の発展,長寿,先祖の為" ,
    "門松の向かって左は何松というか,黒松,赤松,唐松" ,
    "年賀状のお年玉くじの有効期限は,半年間,1年間,2年間" ,
    "七草粥に入れないものはどれ,ドクゼリ,ホトケノザ,ゴギョウ" ,
    "神社での初詣の参拝方法は,2礼2拍手1礼,1礼2拍手2礼,2拍手2礼1拍手" ,
    "厄払いのお布施の相場は,5000円,10000円,30000円" ,
    "仏教での忌服期間は何日間,49日間,13日間,108日間" ,
    "喪中にしてはいけないことは,神社参拝,墓参り,お歳暮" ,
    "夏の土用の丑の日は最大で年何日あるか,2日,1日,4日" ,
    "フランス料理店でナイフを落とした時のマナー違反は,拾う,店員を呼ぶ,ほっとく" ,
    "葬式の際の抹香を摘むときに使わない指は,薬指,人差し指,中指" ,
    "通夜後に飲食しながら故人の話をすることを何という,通夜ぶるまい,施餓鬼,ご説法" ,
    "故人の遺志で香典等を受け取らないことを何という,ご厚志ご辞退,供物・供花ご辞退,ご気持ご辞退" ,
    "香典を渡す際バッグから出して渡すのはマナー違反か,マナー違反,問題なし,むしろそうする" ,
    "母の日にプレゼントする花は,カーネーション,カーネーシュン,カーネーショソ" ,
    "お盆の期間は8月何日から何日,13日～16日,12日～18日,14日～17日" ,
    "七五三参りは何月何日に行うか,11月15日,7月3日,3月17日" ,
    "関東地方でお中元はいつまでに送るか,7月15日,7月31日,8月13日" ,
    "平成28年から適用される新祝日山の日は何月何日か,8月11日,8月18日,8月21日" ,
    "こどもの日を五節句で何という,端午の節句,桃の節句,七夕の節句" ,
    "ひな祭りを五節句で何という,上巳の節句,重陽の節句,人日の節句" ,
    "五節句のうち9月に行われるものを何という,重陽の節句,上巳の節句,人日の節句" ,
    "ひな人形で最上段に飾るのは,内裏雛,随身,繧繝縁" ,
    "七夕の5色の短冊の内で白は何を意味する,天の川,彦星,織姫" ,
    "小春日和とはいつのこと,初冬,冬至,初春" ,
    "節分で邪気除けのために飾るものを何という,柊鰯,椿鯖,柏鯵" ,
    "サンタクロースの出身地は,フィンランド,ドイツ,アイスランド" ,
    "冬至に食べると良いとされるものは,かぼちゃ,大根,白子" ,
    "お彼岸の期間は春分の日と秋分の日の前後何日間か,3日間,1日間,2日間" ,
    "父の日はいつか,6月第3日曜日,5月第2日曜日,6月第1日曜日" ,
    "仏滅の日にしてはいけないことは,結婚式,誕生会,株主総会" ,
    "友引の日にしてはいけないことは,葬式,首脳会談,送別会" ,
    "十五夜と十三夜と十日夜の3回行う月見を何という,三月見,三回月,三見会"
     };

static struct settsumonList sT[200];

void readSettoku2(){
    char *p = std::strtok(setsumons[0], ",");
    int l_num=0;
    int str_num=0;
    for (int i=0; i<200*4; i++) {
        l_num = i;
        
        int ch = l_num % 4;
        
        switch (ch) {
            case 0:
                sT[str_num].setsumon=new char[70];
                std::strcpy(sT[str_num].setsumon, p);
                //log("sT[%i].setsumon = %s",str_num, sT[str_num].setsumon);
                break;
            case 1:
                sT[str_num].choice1=new char[70];
                std::strcpy(sT[str_num].choice1, p);
                //log("sT[%i].choice1 = %s",str_num, sT[str_num].choice1);
                break;
            case 2:
                sT[str_num].choice2=new char[70];
                std::strcpy(sT[str_num].choice2, p);
                //log("sT[%i].choice2 = %s",str_num, sT[str_num].choice2);
                break;
            case 3:
                sT[str_num].choice3=new char[70];
                std::strcpy(sT[str_num].choice3, p);
                //log("sT[%i].choice3 = %s",str_num, sT[str_num].choice3);
                str_num++;
                break;
                
            default:
                break;
        }
        if (ch == 3) {
            p = std::strtok(setsumons[str_num], ",");
        }else{
            p = std::strtok(NULL, ",");
        }
    }
}

static struct settokuList sL[100];

String season;
int seasons;
int stage_num2;
Scene* HelloWorld::scene(int stage_num)
{
    stage_num2 = stage_num;
    season = stage[stage_num];
    
    GameManager gm = *GameManager::getInstance();
    gm.setStageNum(stage_num);
//    if (season.compare("home") == 0) {
//        seasons=0;
//    } else if (season.compare("spring") == 0) {
//        seasons=1;
//    } else if (season.compare("summer") == 0) {
//        seasons=2;
//    } else if (season.compare("autumn") == 0) {
//        seasons=3;
//    } else if (season.compare("winter") == 0) {
//        seasons=4;
//    }
    
    Scene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        //scene = Scene::create();
        scene = Scene::createWithPhysics();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    
    // return the scene
    return scene;
}

void readSettoku(){
    
    char str[10000]="違うんだ！, やめてくれ！, 危ないだろ！, 信じてくれ！, 俺を信用できないのか？, 目に見えるものだけを信じるな！, 愛してるのはお前だけだ！, 俺の愛が分からないのか！？, この口紅の女のことスゲー嫌いだし, 分かって・・くれっ！, 疲れたぁ, doujou, はぁ、はぁ, 俺の目を見てくれ！, そんなわけないだろ！, これは何かの罠だ！, 話せば分かる, 冷静に話し合おう, 一旦落着け！, あの頃みたいに解決できるさ, お前は変わらないな, doujou, 室蘭旅行を思い出すな, 待ってくれ！, タンマ！, まぁまぁまぁ, 何かの間違いだ！, いやこれ口紅じゃないし, 弁当のたらこスパこぼしたんだよ, 明日は有給取るよ, 明日は大事な会議がっ！, 明日は筋肉痛だぜ, それでも俺は受け止めるっ！, すごい剛速球だぜ！, 甲子園出てたんだっけ？, 今のお前も好きだ！, すげぇ顔してるぞ, 昔の日本人が書いたペリーみたいだな, お前が心配なんだよ, 手首のスナップはやめてくれ, 本気出すなよ, 一生お前を幸せにする！, 一牛お前を幸せにする！, 一生お前を辛せにする！, お前じゃないとダメなんだ！, お前じゃないとデメなんだ！, doujou, お前じゃないとダメらんだ！, 今日はとことん話そう, 今日はついてないな, 今日はあの日なのか？, そんなの関係ねぇっ！, そんなこと言ったってしょうがないじゃないか！, 殺す気か！, 絶対にお前を取り戻す！, こんなところでやられてたまるか！, doujou, もう限界かもしれない, 分かった、お前の好きなようにしろ, 分かった、何でも買ってやろう, 分かった、いや分からん, いつも弁当ありがとな, 弁当にたらこスパは無いだろ, doujou, 今日の弁当は特別おいしかったよ, お前の作ったご飯が食べたいよ, 晩飯が冷めるだろ, そろそろやめにしないか？, お前の目は節穴か！？, お前の血は何色だ！？, お前の戦闘力はいくつだ！？, 俺はお前だけを見てるんだ！, 俺はおま、ヘックショイ！, doujou, 俺はおま、ゴホッゴホン！, いい加減決着を付けよう！, ぷよぷよで決着を付けよう！, doujou, 腹を満たしてから決着を付けよう！, お前の気持ちをぶつけてくれ！, お前のいい感じのアレをぶつけてくれ！, doujou, お前のおにぎりをぶつけてくれ！, これは俺達夫婦の愛情試験なんだ！, これは三十路男の猥褻事件なんだ！, doujou, これは満員電車の接触事故なんだ！, 俺は潔白だ！！！, 俺は関白だ！！！, ぼよよ～ん！！！, 俺は無実だぁーーーー！, 俺は水虫だぁーーーー！, doujou, 俺は空腹だぁーーーー！, お前を大切にするって約束したろ？, お前を大切にするって約束したよね？, お前を大切にするって約束したっけ？, 遅くなったけど、今度式を挙げよう, 遅くなったけど、今度新婚旅行しよう, 遅くなったけど、今度ご両親に挨拶に行こう";
    
    char *p = strtok(str, " ,");
    int l_num=0;
    int str_num=0;
    while (p != NULL) {
        
        //printf("+");
        
        if (std::strcmp(p, "doujou") == 0) {
            sL[l_num].doujou=1;
        }else{
            int ch = str_num % 3;
            switch (ch) {
                case 0:
                    sL[l_num].choice1=new char[70];
                    std::strcpy(sL[l_num].choice1, p);
                    break;
                case 1:
                    sL[l_num].choice2=new char[70];
                    std::strcpy(sL[l_num].choice2, p);
                    break;
                case 2:
                    sL[l_num].choice3=new char[70];
                    std::strcpy(sL[l_num].choice3, p);
                    //printf("[%d][%s, %s, %s]\n", l_num, sL[l_num].choice1, sL[l_num].choice2, sL[l_num].choice3);
                    l_num++;
                    break;
                    
                default:
                    break;
            }
            
            str_num++;
        }
        p = strtok(NULL, " ,");
    }
    str_num++;
    
}
int BEST_SCORE=0;
Size screenSize;
int bgm_num=0;
bool init_flg;
ParticleGalaxy* pParticle;
// on "init" you need to initialize your instance
int clear_seii[25]{0,0,4,0,0,6,0,0,8,0,0,10,0,0,12,0,0,14,0,0,16,0,0,18,20};
int clear_time[25]{60,90,0,60,90,0,90,120,0,90,120,0,120,150,0,120,150,0,150,180,0,150,180,0,180};
bool HelloWorld::init()
{
    char stage_title[100];
    //sprintf(stage_title,"Stage ");
    sprintf(stage_title,"Stage %d   [%s round]",(stage_num2+1), season.getCString());
    CCLabelTTF *text = CCLabelTTF::create(stage_title, "Arial", 32);
    text->setColor(Color3B::WHITE);
    text->setPosition(CCPointMake(200, 1100));
    //text->setColor(Color3B::BLACK);
    this->addChild(text,3);
    
    char stage_clear[100];
    if(clear_seii[stage_num2] != 0){
        sprintf(stage_clear,"Stage_Clear you need answer about %d times",clear_seii[stage_num2]);
    }else{
        sprintf(stage_clear,"Stage_Clear you need escape about %d seconds",clear_time[stage_num2]);
    }
    CCLabelTTF *text2 = CCLabelTTF::create(stage_clear, "Arial", 32);
    text2->setColor(Color3B::WHITE);
    text2->setPosition(CCPointMake(200, 1000));
    //text->setColor(Color3B::BLACK);
    this->addChild(text2,3);
    
    //char apiKey[] = "14d053f4456ddde402acb72c1f81288bac66dcdd";
    //char spotID[] = "351624";
    //    char apiKey[] = "14d053f4456ddde402acb72c1f81288bac66dcdd";
    //    char spotID[] = "351624";
    //NendModule::createNADViewBottom(apiKey, spotID);
    
    _targets = Vector<Sprite*>(100);
    _projectiles = Vector<Sprite*>(100);
    
    userDefault = UserDefault::getInstance();
    BEST_SCORE = userDefault->getIntegerForKey("integerKey", 0);
    screenSize = Director::getInstance()->getVisibleSize();
    
    /*CCSize size = CCDirector::sharedDirector()->getWinSize();
     CCSprite* sprite = CCSprite::create("Icon-72.png");
     CCProgressTimer* timer = CCProgressTimer::create(sprite);
     timer->setType(kCCProgressTimerTypeRadial);
     timer->setPosition(ccp(size.width/2, size.height/2));
     timer->setPercentage(0.0f);
     this->addChild(timer, 1, 1);*/
    
    elapsedTime=0.0;
    s_num=START_SEII;
    touch_flg = true;
    cd_flg = false;
    lifeup_flg = false;
    hou_flg=false;
    cuv_flg = false;
    bus_flg=false;
    pause_flg=false;
    readSettoku();
    if(first_flg == false){
        readSettoku2();
        first_flg = true;
    }
    bool bRet = false;
    do
    {
        h_num=START_LIFE;
        oni_flg=false;
        
        // init rand
        srand((unsigned)time( NULL ));
        
        //CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("当たる（刺）.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("当たる（割）.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("当たる（軽）.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("当たる（重）.mp3");
        
        
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        
        //CC_BREAK_IF(! CCLayerColor::initWithColor( Color4B(255,255,255,255) ) );
        CC_BREAK_IF(! CCLayerColor::initWithColor( Color4B(0,0,0,0) ) );
        
        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////
        
        // 1. Add a menu item with "X" image, which is clicked to quit the program.
        
        // Create a "close" menu item with close icon, it's an auto release object.
        //		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
        //                                                              "CloseNormal.png",
        //                                                              "CloseSelected.png",
        //                                                              this,
        //                                                              menu_selector(HelloWorld::menuCloseCallback));
        //		CC_BREAK_IF(! pCloseItem);
        
        // Place the menu item bottom-right conner.
        Size visibleSize = Director::getInstance()->getVisibleSize();
        //        Point origin = CCDirector::getInstance()->getVisibleOrigin();
        //
        //		pCloseItem->setPosition(Point(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2,
        //                                    origin.y + pCloseItem->getContentSize().height/2));
        //
        //        wind_width = visibleSize.width;
        //        wind_height = visibleSize.height;
        //
        //        //log("++++++++size  x:%f, y:%f", visibleSize.width, visibleSize.height);
        //
        //		// Create a menu with the "close" menu item, it's an auto release object.
        //		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        //		pMenu->setPosition(PointZero);
        //		CC_BREAK_IF(! pMenu);
        
        // Add the menu to HelloWorld layer as a child layer.
        //		this->addChild(pMenu, 1);
        
        DrawScene();
        
        /////////////////////////////
        // 2. add your codes below...
        player = Sprite::create("スーツ_止１前.png", Rect(0, 0, 43, 62) );
        
        player->setPosition( Point(visibleSize.width/2,
                                   player->getContentSize().height/2 + visibleSize.height/2) );
        this->addChild(player);
        
        
        // 剛体の生成
        auto material = PHYSICSBODY_MATERIAL_DEFAULT;
        material.density     = 1.0f; // 密度
        material.restitution = 0.9f; // 反発係数
        material.friction    = 0.5f; // 摩擦係数
        auto pBody = PhysicsBody::createBox(player->getContentSize(), material);
        //pBody->setDynamic(true); // 地面は重力の影響を受けない
        
        pBody->setMass(1.0f); // 重さ
        
        // スプライトに剛体を関連付ける
        player->setPhysicsBody(pBody);
        
        
        this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );
        
        // タッチイベントを追加する場合
        getEventDispatcher()->setEnabled(true);
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        auto listener = EventListenerTouchOneByOne::create();
        


        //タッチ開始
        listener->onTouchBegan = [this](Touch* touch, Event* event){
            //log("TouchBegan");
            Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
            pParticle = ParticleGalaxy::createWithTotalParticles(1000);
            pParticle->setPosition(touchPoint);
            this->addChild(pParticle);
            return true;
        };
        
        //タッチ中
        listener->onTouchMoved = [](Touch* touch, Event* event){
            //log("TouchMoved");
            Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
            pParticle->setPosition(touchPoint);
            return true;
        };
        
        //タッチ終了
        listener->onTouchEnded = [this](Touch* touch, Event* event){
            //log("TouchEnded");
            this->removeChild(pParticle);
        };
        
        //イベントリスナーを登録
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        
        //_targets = new CCArray;
        //_projectiles = new CCArray;
        
        // use updateGame instead of update, otherwise it will conflit with SelectorProtocol::update
        // see http://www.cocos2d-x.org/boards/6/topics/1478
        this->schedule( schedule_selector(HelloWorld::updateGame) );
        
        //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background-music-aac.wav", true);
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.7);
        char* stage_bgm[25]={"春は揚げ物.mp3", "春は揚げ物.mp3", "死逃.mp3", "春は揚げ物.mp3", "春は揚げ物.mp3", "死逃.mp3", "夏は酔う.mp3", "夏は酔う.mp3", "死逃.mp3", "夏は酔う.mp3", "夏は酔う.mp3", "死逃.mp3", "秋は靴ずれ.mp3", "秋は靴ずれ.mp3", "死逃.mp3", "秋は靴ずれ.mp3", "秋は靴ずれ.mp3", "死逃.mp3", "冬は萎めて.mp3", "冬は萎めて.mp3", "死逃.mp3", "冬は萎めて.mp3", "冬は萎めて.mp3", "死逃.mp3", "LAST ESCAPE.mp3"};
        bgm_num = stage_num2;
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(stage_bgm[bgm_num], true);
        //bgm_num = (bgm_num +1) % 25;

        init_flg = false;
        //CCLOG("-----------[%i]---------",bgm_num);
        bRet = true;
    } while (0);
    
    return bRet;
}

int se1w=107;

int seh=140;
int bgh=seh+399;
int seih=bgh+361;
int lifeh=seih+81;
int infoh=lifeh+81;
Sprite *yo1, *yo2 , *yo3, *yo4;
//ParticleSystemQuad* particle;

void HelloWorld::DrawScene(void){
    
    //ParticleSystemQuad* particle = ParticleSystemQuad::create("player-aura.plist");
    
    //particle->setPosition(320,530);

    //settoku
    settokuOutput(0);
    
    //info
    InfoOutput();
    
    //heart
    lifeOutput();
    
    //Seii
    SeiiOutput();
    
    // background image
    
    if (screenSize.height > 960)
    {
        if(season.compare("home") == 0){
            
            Sprite *bg = Sprite::create(bg0_gif, Rect(0, 0, 640, 640) );
            //bg->setScale(0.7);
            bg->setPosition(Point(320,580));
            this->addChild(bg);
            
        }else if(season.compare("spring") == 0){
            
            Sprite *bg = Sprite::create(bg1_gif, Rect(0, 0, 640, 640) );
            //bg->setScale(0.7);
            bg->setPosition(Point(320,580));
            this->addChild(bg);
            
            Sprite *sa = Sprite::create(sakura_png);
            sa->setPosition(Point(130,840));
            this->addChild(sa, 2);
            
            Sprite *sa2 = Sprite::create(sakura_png);
            sa2->setPosition(Point(500,320));
            this->addChild(sa2, 2);
            
            
            yo1 = Sprite::create(yopparai1_png);
            yo1->setPosition(Point(420,810));
            this->addChild(yo1);
            
            yo2 = Sprite::create(yopparai1_png);
            yo2->setPosition(Point(110,550));
            this->addChild(yo2);
            
            yo3 = Sprite::create(yopparai1_png);
            yo3->setPosition(Point(280,370));
            this->addChild(yo3);
            
            yo4 = Sprite::create(yopparai1_png);
            yo4->setPosition(Point(550,640));
            this->addChild(yo4);
            
            //cocos2dx2.x
            //Animation(の初期化
            Animation* animation = Animation::create();
            
            //画像を配列に代入
            //Vector<String> *yo;
            //yo->pushBack(yopparai1_png);
            //yo.pushBack(yopparai2_png);
            
            //CCObject *object = NULL;
            //int i = 0;
            //CCARRAY_FOREACH(yo, object) {
            //char szImageFileName[128] = {0};
            //sprintf(szImageFileName, ((CCString *)object)->getCString(), i);
            //log("%s",((CCString *)object)->getCString());
            //animation->addSpriteFrameWithFile(yopparai1_png);
            //i++;
            //}
            
            
            animation->addSpriteFrameWithFile(yopparai1_png);
            animation->addSpriteFrameWithFile(yopparai2_png);
            
            //animation->addSpriteFrameWithFile("スーツ_止前.png");
            //animation->addSpriteFrameWithFile("スーツ_走１前.png");
            
            
            //アニメーションの設定 1 : 1コマ0.1秒で切り替える。
            animation->setDelayPerUnit(0.5);
            
            //距離によってアニメーションのループ回数を変更する
            animation->setLoops(1000000);
            
            //アニメーションの設定
            Animate* animate = Animate::create(animation);
            
            //cocos2dx2.x
            
            Animate *action = Animate::create(animation);
            CCRepeatForever *anime = CCRepeatForever::create(action);
            action->setTag(801);
            yo1->runAction(action);
            
            //Animation(の初期化
            animation = Animation::create();
            
            animation->addSpriteFrameWithFile(yopparai1_png);
            animation->addSpriteFrameWithFile(yopparai2_png);
            
            //animation->addSpriteFrameWithFile("スーツ_止前.png");
            //animation->addSpriteFrameWithFile("スーツ_走１前.png");
            
            
            //アニメーションの設定 1 : 1コマ0.1秒で切り替える。
            animation->setDelayPerUnit(0.5);
            
            //距離によってアニメーションのループ回数を変更する
            animation->setLoops(1000000);
            
            //アニメーションの設定
            animate = Animate::create(animation);
            
            //cocos2dx2.x
            
            action = Animate::create(animation);
            anime = CCRepeatForever::create(action);
            action->setTag(802);
            yo2->runAction(action);
            
            //Animation(の初期化
            animation = Animation::create();
            
            animation->addSpriteFrameWithFile(yopparai1_png);
            animation->addSpriteFrameWithFile(yopparai2_png);
            
            //animation->addSpriteFrameWithFile("スーツ_止前.png");
            //animation->addSpriteFrameWithFile("スーツ_走１前.png");
            
            
            //アニメーションの設定 1 : 1コマ0.1秒で切り替える。
            animation->setDelayPerUnit(0.5);
            
            //距離によってアニメーションのループ回数を変更する
            animation->setLoops(1000000);
            
            //アニメーションの設定
            animate = Animate::create(animation);
            
            //cocos2dx2.x
            
            action = Animate::create(animation);
            anime = CCRepeatForever::create(action);
            action->setTag(803);
            yo3->runAction(action);
            
            //Animation(の初期化
            animation = Animation::create();
            
            animation->addSpriteFrameWithFile(yopparai1_png);
            animation->addSpriteFrameWithFile(yopparai2_png);
            
            //animation->addSpriteFrameWithFile("スーツ_止前.png");
            //animation->addSpriteFrameWithFile("スーツ_走１前.png");
            
            
            //アニメーションの設定 1 : 1コマ0.1秒で切り替える。
            animation->setDelayPerUnit(0.5);
            
            //距離によってアニメーションのループ回数を変更する
            animation->setLoops(1000000);
            
            //アニメーションの設定
            animate = Animate::create(animation);
            
            //cocos2dx2.x
            
            action = Animate::create(animation);
            anime = CCRepeatForever::create(action);
            action->setTag(804);
            yo4->runAction(action);
            
        } else if(season.compare("summer") == 0){
            
            Sprite *bg = Sprite::create(bg2_gif, Rect(0, 0, 640, 640) );
            //bg->setScale(0.7);
            bg->setPosition(Point(320,580));
            this->addChild(bg);
            
            Sprite *ps = Sprite::create(bg2_2_gif);
            //bg->setScale(0.7);
            ps->setPosition(Point(320,780));
            this->addChild(ps, 2);
        } else if(season.compare("autumn") == 0){
            
            Sprite *bg = Sprite::create(bg3_gif, Rect(0, 0, 640, 640) );
            //bg->setScale(0.7);
            bg->setPosition(Point(320,580));
            this->addChild(bg);
            //
            //            Sprite *hu = Sprite::create(hubuki_png);
            //            hu->setPosition(Point(100,540));
            //            this->addChild(hu);
        } else if(season.compare("winter") == 0){
            
            Sprite *bg = Sprite::create(bg4_gif, Rect(0, 0, 640, 640) );
            //bg->setScale(0.7);
            bg->setPosition(Point(320,580));
            this->addChild(bg);
            //
            //            Sprite *hu = Sprite::create(hubuki_png);
            //            hu->setPosition(Point(100,540));
            //            this->addChild(hu);
        }
        
        Sprite *time = Sprite::create(TIME_gif, Rect(0, 0, 100, 60) );
        time->setPosition(Point(590,930));
        this->addChild(time,4);
        
        //タイマーを表示
        LabelTTF* timerLabel = LabelTTF::create("     0", settoku_font, 24.0f);
        //CCString* timeString = CCString::createWithFormat("%8.0f", elapsedTime);
        
        timerLabel->setPosition(Point(580, 920));
        timerLabel->setTag(100);
        this->addChild(timerLabel,4);
        
        Sprite *pause = Sprite::create(PAUSE_gif, Rect(0, 0, 100, 176) );
        pause->setPosition(Point(590,1048));
        this->addChild(pause,4);
        
        
        //SCOREを表示
//        LabelTTF* scoreLabel = LabelTTF::create("0", settoku_font, 36.0f);
//        scoreLabel->setPosition(Point(470, lifeh+81));
//        scoreLabel->setTag(200);
//        this->addChild(scoreLabel);
        
    }else{
        Sprite *bg = Sprite::create(bg1_gif, Rect(0, 0, 640, 640) );
        //bg->setScale(0.7);
        bg->setPosition(Point(320,bgh+25));
        this->addChild(bg);
        
        //タイマーを表示
        LabelTTF* timerLabel = LabelTTF::create("     0", settoku_font, 36.0f);
        //CCString* timeString = CCString::createWithFormat("%8.0f", elapsedTime);
        
        timerLabel->setPosition(Point(170, lifeh+2));
        timerLabel->setTag(100);
        this->addChild(timerLabel);
        
        //SCOREを表示
        LabelTTF* scoreLabel = LabelTTF::create("0", settoku_font, 36.0f);
        scoreLabel->setPosition(Point(470, lifeh+2));
        scoreLabel->setTag(200);
        this->addChild(scoreLabel);
    }
    
    //this->addChild(particle);
}

int se_ls;

int ch_ls;

void HelloWorld::changeSettoku(float dt){
    touch_flg = true;
    settokuOutput(0);
}

int setsu[25] = {1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5};
void HelloWorld::settokuOutput(int ch){
    
    //printf("[%s, %s, %s]\n", sL[0].choice1, sL[0].choice2, sL[0].choice3);
    
    
    int f_size, s_size;
    if (screenSize.height > 960)
    {
        f_size = 28;
        s_size = 20;
    }else{
        f_size = 24;
        s_size = 16;
    }
    
    int se2w=se1w+212;
    
    int se3w=se2w+214;
    
    // settoku1 bg
    
    if (screenSize.height > 960)
    {
        settoku1 = Sprite::create(settoku1_gif, Rect(0, 0, 214,80) );
        settoku1->setPosition(Point(se1w,seh));
        this->addChild(settoku1,4);
    }else{
        settoku1 = Sprite::create(settoku1_gif, Rect(0, 0, 215, 102) );
        settoku1->setPosition(Point(se1w,seh+54));
        this->addChild(settoku1,4);
    }
    
    // settoku2 bg
    
    if (screenSize.height > 960)
    {
        settoku2 = Sprite::create(settoku2_gif, Rect(0, 0, 212, 80) );
        settoku2->setPosition(Point(se2w,seh));
        this->addChild(settoku2,4);
    }else{
        settoku2 = Sprite::create(settoku2_gif, Rect(0, 0, 214, 102) );
        settoku2->setPosition(Point(se2w,seh+54));
        this->addChild(settoku2,4);
    }
    
    // settoku3 bg
    if (screenSize.height > 960)
    {
        settoku3 = Sprite::create(settoku3_gif, Rect(0, 0, 214, 80) );
        settoku3->setPosition(Point(se3w,seh));
        this->addChild(settoku3,4);
    }else{
        settoku3 = Sprite::create(settoku3_gif, Rect(0, 0, 214, 102) );
        settoku3->setPosition(Point(se3w,seh+54));
        this->addChild(settoku3,4);
    }
    
    // setsumon
    
    int setsuh = seh+80;
    
    setsumon = Sprite::create(setsumon_png, Rect(0, 0, 640, 80) );
    setsumon->setPosition(Point(320,setsuh));
    this->addChild(setsumon,4);
    
    // 剛体の生成
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.density     = 1.0f; // 密度
    material.restitution = 0.9f; // 反発係数
    material.friction    = 0.5f; // 摩擦係数
    auto pBody = PhysicsBody::createBox(setsumon->getContentSize(), material);
    pBody->setDynamic(false); // 地面は重力の影響を受けない
    
    // スプライトに剛体を関連付ける
    setsumon->setPhysicsBody(pBody);
    
    if(setsu[stage_num2] == 5){
        se_ls=rand()%200;
    }else{
        se_ls=rand()%50+(setsu[stage_num2]-1)*50;
    }
    
    ch_ls=rand()%3;
    
    int sc_h;
    if (screenSize.height > 960)
    {
        sc_h = 0;
    }else{
        sc_h = 50;
    }
    
    if (ch_ls == 0) {
        // setsumon label
        
        LabelTTF* setsuLabel = LabelTTF::create(sT[se_ls].setsumon, settoku_font, s_size);
        //printf("ch0 %d %s %s %s", se_ls, sT[se_ls].choice1, sT[se_ls].choice2, sT[se_ls].choice3);
        setsuLabel->setDimensions(Size(890,0));
        setsuLabel->setPosition(Point(se1w+150,seh+sc_h+100));
        setsuLabel->setColor(Color3B::BLACK);
        this->addChild(setsuLabel,4);
        
        // settoku1 label
        
        LabelTTF* s1Label = LabelTTF::create(sT[se_ls].choice1, settoku_font, f_size);
        //printf("%d %s %s %s", se_ls, sT[se_ls].choice1, sT[se_ls].choice2, sT[se_ls].choice3);
        s1Label->setDimensions(Size(190,0));
        s1Label->setPosition(Point(se1w,seh+sc_h));
        this->addChild(s1Label,4);
        
        // settoku2 label
        
        LabelTTF* s2Label = LabelTTF::create(sT[se_ls].choice2, settoku_font, f_size);
        s2Label->setDimensions(Size(190,0));
        s2Label->setPosition(Point(se2w,seh+sc_h));
        this->addChild(s2Label,4);
        
        // settoku3 label
        
        LabelTTF* s3Label = LabelTTF::create(sT[se_ls].choice3, settoku_font, f_size);
        s3Label->setDimensions(Size(190,0));
        s3Label->setPosition(Point(se3w,seh+sc_h));
        this->addChild(s3Label,4);
        
    }else if (ch_ls == 1) {
        // setsumon label
        
        LabelTTF* setsuLabel = LabelTTF::create(sT[se_ls].setsumon, settoku_font, s_size);
        //printf("ch1 %d %s %s %s", se_ls, sT[se_ls].choice1, sT[se_ls].choice2, sT[se_ls].choice3);
        setsuLabel->setDimensions(Size(890,0));
        setsuLabel->setPosition(Point(se1w+150,seh+sc_h+100));
        setsuLabel->setColor(Color3B::BLACK);
        this->addChild(setsuLabel,4);
        
        // settoku1 label
        
        LabelTTF* s1Label = LabelTTF::create(sT[se_ls].choice3, settoku_font, f_size);
        //printf("%d %s %s %s", se_ls, sT[se_ls].choice1, sT[se_ls].choice2, sT[se_ls].choice3);
        s1Label->setDimensions(Size(190,0));
        s1Label->setPosition(Point(se1w,seh+sc_h));
        this->addChild(s1Label,4);
        
        // settoku2 label
        
        LabelTTF* s2Label = LabelTTF::create(sT[se_ls].choice1, settoku_font, f_size);
        s2Label->setDimensions(Size(190,0));
        s2Label->setPosition(Point(se2w,seh+sc_h));
        this->addChild(s2Label,4);
        
        // settoku3 label
        
        LabelTTF* s3Label = LabelTTF::create(sT[se_ls].choice2, settoku_font, f_size);
        s3Label->setDimensions(Size(190,0));
        s3Label->setPosition(Point(se3w,seh+sc_h));
        this->addChild(s3Label,4);
        
    }else if (ch_ls == 2) {
        // setsumon label
        
        LabelTTF* setsuLabel = LabelTTF::create(sT[se_ls].setsumon, settoku_font, s_size);
        //printf("ch2 %d %s %s %s", se_ls, sT[se_ls].choice1, sT[se_ls].choice2, sT[se_ls].choice3);
        setsuLabel->setDimensions(Size(890,0));
        setsuLabel->setPosition(Point(se1w+150,seh+sc_h+100));
        setsuLabel->setColor(Color3B::BLACK);
        this->addChild(setsuLabel,4);
        
        // settoku1 label
        
        LabelTTF* s1Label = LabelTTF::create(sT[se_ls].choice2, settoku_font, f_size);
        //printf("%d %s %s %s", se_ls, sT[se_ls].choice1, sT[se_ls].choice2, sT[se_ls].choice3);
        s1Label->setDimensions(Size(190,0));
        s1Label->setPosition(Point(se1w,seh+sc_h));
        this->addChild(s1Label,4);
        
        // settoku2 label
        
        LabelTTF* s2Label = LabelTTF::create(sT[se_ls].choice3, settoku_font, f_size);
        s2Label->setDimensions(Size(190,0));
        s2Label->setPosition(Point(se2w,seh+sc_h));
        this->addChild(s2Label,4);
        
        // settoku3 label
        
        LabelTTF* s3Label = LabelTTF::create(sT[se_ls].choice1, settoku_font, f_size);
        s3Label->setDimensions(Size(190,0));
        s3Label->setPosition(Point(se3w,seh+sc_h));
        this->addChild(s3Label,4);
    }
}

void HelloWorld::SeiiOutput(void){
    
    // seii bg
    
    if (screenSize.height > 960)
    {
        Sprite *seii = Sprite::create(seii_gif, Rect(0, 0, 540, 30) );
        seii->setPosition(Point(270,915));
        this->addChild(seii, 3);
        int sp = 80;
        int sp_w = 17;
        
        // spade
        
        for (int i=0; i<s_num; i++) {
            Sprite *spade = Sprite::create(spade_jpeg, Rect(0, 0, 15, 18) );
            //spade->setScale(0.09);
            if (i < 10) {
                spade->setPosition(Point(sp+(sp_w*i),seih+16));
            }else{
                spade->setPosition(Point(sp+(sp_w*(i-10)),seih-20));
            }
            this->addChild(spade, 3);
        }
    }
    else{
        Sprite *seii = Sprite::create(seii_gif, Rect(0, 0, 640, 41) );
        seii->setPosition(Point(320,seih+5));
        this->addChild(seii, 3);
        
        
        int sp = 17;
        int sp_w = 14;
        
        // spade
        
        for (int i=0; i<s_num; i++) {
            Sprite *spade = Sprite::create(spade_jpeg, Rect(0, 0, 14, 17) );
            //spade->setScale(0.05);
            if (i < 16) {
                //log("spade %d",sp+(sp_w*i));
                spade->setPosition(Point(sp+(sp_w*i),940));
            }
            this->addChild(spade, 3);
        }
    }
    
}

void HelloWorld::lifeOutput(void){
    
    // life bg
    
    if (screenSize.height > 960)
    {
        Sprite *life = Sprite::create(LIFE_gif, Rect(0, 0, 540, 30) );
        life->setPosition(Point(270,945));
        this->addChild(life, 3);
    }
    else{
        Sprite *life = Sprite::create(LIFE_gif, Rect(0, 0, 640, 41) );
        life->setPosition(Point(320,lifeh-35));
        this->addChild(life, 3);
    }
    
    
    if (screenSize.height > 960)
    {
        //heart
        int hr = 80;
        int hr_w = 17;
        
        for (int i=0; i<h_num; i++) {
            Sprite *heart = Sprite::create(heart_jpeg, Rect(0, 0, 15, 18) );
            //heart->setScale(0.09);
            
            heart->setPosition(Point(hr+(hr_w*i),945));
            //            if (i < 10) {
            //                heart->setPosition(Point(hr+(hr_w*i),945));
            //            }else{
            //                heart->setPosition(Point(hr+(hr_w*(i-10)),lifeh-26*2));
            //            }
            
            
            this->addChild(heart,3);
        }
    }else{
        //heart
        int hr = 94;
        int hr_w = 35;
        
        for (int i=0; i<h_num; i++) {
            Sprite *heart = Sprite::create(heart_jpeg, Rect(0, 0, 500, 500) );
            heart->setScale(0.05);
            
            if (i < 16) {
                heart->setPosition(Point(hr+(hr_w*i),lifeh-40));
            }
            
            this->addChild(heart,3);
        }
        
    }
    
}

void HelloWorld::InfoOutput(void){
    
    // info bg
    if (screenSize.height > 960)
    {
//        Sprite *info = Sprite::create(info_gif, Rect(0, 0, 642, 81) );
//        info->setPosition(Point(320,infoh));
//        this->addChild(info);
    }
    else{
        //Sprite *info = Sprite::create(info_gif, Rect(0, 0, 640, 41) );
        //info->setPosition(Point(320,infoh-75));
        //this->addChild(info);
    }
    
}

void HelloWorld::AnserOutput(int touchNum){
    
    // Anser bg
    
    Sprite *Anser;
    
    int an=touchNum;
    
    if (ch_ls == 1) {
        switch (touchNum) {
            case 1:
                an = 3;
                break;
            case 2:
                an = 1;
                break;
            case 3:
                an = 2;
                break;
                
            default:
                break;
        }
    }else if (ch_ls == 2){
        switch (touchNum) {
            case 1:
                an = 2;
                break;
            case 2:
                an = 3;
                break;
            case 3:
                an = 1;
                break;
                
            default:
                break;
        }
    }
    
    int hf=an;
    
    if (screenSize.height > 960)
    {
        if (hf == 1) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("正解.mp3");
            Anser = Sprite::create(seikai_gif, Rect(0, 0, 212, 80)   );
            //Anser = Sprite::create(seikai_gif);
            //Anser->setScale(0.8);
            if (s_num < SEII_MAX) {
                s_num++;
                SeiiOutput();
            }
        }else if(hf == 2){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("はずれ.mp3");
            Anser = Sprite::create(hazure_gif, Rect(0, 0, 212, 90) );
            Anser->setScale(1.7,0.9);
            hou_flg = true;
        }else if(hf == 3){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("同情.mp3");
            Anser = Sprite::create(doujou_gif, Rect(0, 0, 212, 80) );
            oni_flg=true;
        }
        touch_flg = false;
        this->scheduleOnce(schedule_selector(HelloWorld::changeSettoku), 2.0);
        
        if(hou_flg){
            Anser->setPosition(Point(185+((touchNum-1)*214),seh));
        }
        else{
            Anser->setPosition(Point(105+((touchNum-1)*214),seh));
        }
        this->addChild(Anser,4);
        
    }else{
        
        if (hf == 1) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("正解.mp3");
            //Anser = Sprite::create(seikai_gif, Rect(0, 0, 144, 118) );
            Anser = Sprite::create(seikai_gif, Rect(0, 0, 212, 80)  );
            //Anser->setScale(0.8);
            if (s_num < SEII_MAX) {
                s_num++;
                SeiiOutput();
            }
        }else if(hf == 2){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("はずれ.mp3");
            Anser = Sprite::create(hazure_gif, Rect(0, 0, 212, 80) );
            //Anser->setScale(0.8);
            hou_flg = true;
        }else if(hf == 3){
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("同情.mp3");
            Anser = Sprite::create(doujou_gif, Rect(0, 0, 212, 80) );
            oni_flg=true;
        }
        
        touch_flg = false;
        this->scheduleOnce(schedule_selector(HelloWorld::changeSettoku), 2.0);
        
        Anser->setPosition(Point(116+((touchNum-1)*214),seh+50));
        this->addChild(Anser,4);
    }
    
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::getInstance()->end();
}

int hirai_num[25]={0,0,0,4,4,4,1,1,1,5,5,5,2,2,2,6,6,6,3,3,3,7,7,7,8};
//char hirai[9][200]={
//    "クッション.png,スリッパ.png,本.png,コップ.png,花瓶.png",
//    "クッション.png,バランスボール.png,コップ.png,花瓶.png,CD.png",
//    "コップ.png,バランスボール.png,CD.png,皿.png,テーブル.png",
//    "本.png,CD.png,皿.png,テーブル.png,タンス.png",
//    "空き缶.png,ゴミ袋.png,オードブル.png,焼き鳥.png,酒瓶.png",
//    "空き缶.png,焼きもろこし.png,浮き輪.png,スイカボール.png,スイカ.png",
//    "ゴミ袋.png,酒瓶.png,ペナント.png,みたらし団子.png,ニホンザル.png",
//    "ストック.png,スノーボード.png,雪だるま.png,雪玉（小）.png,雪玉（大）.png",
//        "クッション.png,スリッパ.png,本.png,コップ.png,花瓶.png,バランスボール.png,CD.png,皿.png,テーブル.png,タンス.png"};
    //"クッション.png,スリッパ.png,本.png,コップ.png,花瓶.png,バランスボール.png,CD.png,皿.png,テーブル.png,タンス.png,空き缶.png,ゴミ袋.png,オードブル.png,焼き鳥.png,酒瓶.png,焼きもろこし.png,浮き輪.png,スイカボール.png,スイカ.png,ペナント.png,みたらし団子.png,ニホンザル.png,ストック.png,スノーボード.png,雪だるま.png,雪玉（小）.png,雪玉（大）.png"};

char *tonderu[20];
// cpp with cocos2d-x
void HelloWorld::addTarget()
{
    bgm_num = stage_num2;
    if(!pause_flg){
    char *p;
    int str_num=0;
    
    if (init_flg == false) {
        char hirai[9][500]={
            "クッション.png,スリッパ.png,本.png,コップ.png,花瓶.png",
            "クッション.png,バランスボール.png,コップ.png,花瓶.png,CD.png",
            "コップ.png,バランスボール.png,CD.png,皿.png,テーブル.png",
            "本.png,CD.png,皿.png,テーブル.png,タンス.png",
            "空き缶.png,ゴミ袋.png,オードブル.png,焼き鳥.png,酒瓶.png",
            "空き缶.png,焼きもろこし.png,浮き輪.png,スイカボール.png,スイカ.png",
            "ゴミ袋.png,酒瓶.png,ペナント.png,みたらし団子.png,ニホンザル.png",
            "ストック.png,スノーボード.png,雪だるま.png,雪玉（小）.png,雪玉（大）.png",
            "クッション.png,スリッパ.png,本.png,コップ.png,花瓶.png,バランスボール.png,CD.png,皿.png,テーブル.png,タンス.png,空き缶.png,ゴミ袋.png,オードブル.png,焼き鳥.png,酒瓶.png,焼きもろこし.png,浮き輪.png,スイカボール.png,スイカ.png,ペナント.png,みたらし団子.png,ニホンザル.png,ストック.png,スノーボード.png,雪だるま.png,雪玉（小）.png,雪玉（大）.png"};
        log("bgm_num = %d",bgm_num);
        p = std::strtok(hirai[hirai_num[bgm_num]], ",");
                    log("bgm_num = %s",hirai[hirai_num[bgm_num]]);
        while (p != NULL) {
            tonderu[str_num] = new char[70];
            std::strcpy(tonderu[str_num], p);
            str_num++;
            //CCLOG("str[%i]:%s",str_num,p);
            p = strtok(NULL, ",");
        }
        init_flg = true;
    }
    
    Sprite *target;
    if (oni_flg) {
        target = Sprite::create("おにぎり.png");
        target->setScale(1.5);
        target->setTag(999);
        oni_flg = false;
    }else if(hou_flg){
        target = Sprite::create("包丁.png");
        target->setTag(4);
    }else{
        //log("this time : %f", elapsedTime);
        int chara = rand()%100;
        if (chara < 25) {
            target = Sprite::create(tonderu[0]);
            target->setTag(2);
        }else if(chara < 50){
            target = Sprite::create(tonderu[1]);
            target->setTag(2);
        }else if(chara < 75){
            target = Sprite::create(tonderu[2]);
            target->setTag(1);
        }else if(chara < 77){
            target = Sprite::create(tonderu[3]);
            target->setTag(1);
        }else if(chara < 92){
            target = Sprite::create(tonderu[4]);
            target->setTag(1);
            //bus_flg=true;
        }else if(chara < 100){
            target = Sprite::create(tonderu[4]);
            target->setTag(1);
            cuv_flg = true;
        }
    }
    
    // Determine where to spawn the target along the Y axis
    Size winSize = CCDirector::getInstance()->getWinSize();
    float minY = target->getContentSize().height/2+200;
    float maxY = minY + 640 -  target->getContentSize().height/2;
    int rangeY = (int)(maxY - minY);
    //log("rangeY %d",rangeY);
    // srand( TimGetTicks() );
    int actualY = ( rand() % rangeY ) + (int)minY;
    
    float minX = 0;
    float maxX = CCDirector::getInstance()->getWinSize().width;
    int rangeX = (int)(maxX - minX);
    // srand( TimGetTicks() );
    int actualX = ( rand() % rangeX ) + (int)minX;
    //log("%d", CCDirector::getInstance()->getVisibleSize().width);
    //log("%f %f", minX, maxX);
    //log("%f %d", actualY-minY, actualY);
    
    // Determine speed of the target
    int minDuration = (int)2.0;
    int maxDuration = (int)4.0;
    int rangeDuration = maxDuration - minDuration;
    // srand( TimGetTicks() );
    int actualDuration = ( rand() % rangeDuration ) + minDuration +1;
    //log("$$$$$$$$%d",actualDuration);
    
    int count;
    srand((unsigned)time( NULL ));
    count = rand()%4;
    
    int curve_count = count%2;
    
    int obli_cont = rand()%450+300;
    
    int tate_count = rand()%640;
    
    //log("rand = %d",count);
    //count =0;
    
    if (cuv_flg) {
        
        if (curve_count == 0) {
            target->setPosition(
                                Point(winSize.width + (target->getContentSize().width),
                                      CCDirector::getInstance()->getVisibleOrigin().y + actualY) );
            
            this->addChild(target);
            
            ccBezierConfig bezier;
            bezier.controlPoint_1 = Point(winSize.width + (target->getContentSize().width),
                                          CCDirector::getInstance()->getVisibleOrigin().y + actualY);
            
            bezier.controlPoint_2 = Point((winSize.width + (target->getContentSize().width))/2, (CCDirector::getInstance()->getVisibleOrigin().y + actualY)/2);
            
            bezier.endPosition = Point(-target->getContentSize().width/2, actualY);
            
            ActionInterval* actionBezier = CCBezierTo::create((float)actualDuration, bezier);
            target->runAction(actionBezier);
        }else{
            target->setPosition(
                                Point(winSize.width + (target->getContentSize().width),
                                      CCDirector::getInstance()->getVisibleOrigin().y + actualY) );
            
            this->addChild(target);
            
            ccBezierConfig bezier;
            bezier.controlPoint_1 = Point(0,
                                          CCDirector::getInstance()->getVisibleOrigin().y + actualY);
            
            bezier.controlPoint_2 = Point((winSize.width + (target->getContentSize().width))/2, (CCDirector::getInstance()->getVisibleOrigin().y + actualY)/2);
            
            bezier.endPosition = Point(winSize.width + target->getContentSize().width, actualY);
            
            target->setPosition(
                                Point(0,
                                      CCDirector::getInstance()->getVisibleOrigin().y + actualY) );
            
            ActionInterval* actionBezier = CCBezierTo::create((float)actualDuration, bezier);
            target->runAction(actionBezier);
        }
        
        cuv_flg = false;
    }
    
    // 右から
    else if (count == 0) {
        // Create the target slightly off-screen along the right edge,
        // and along a random position along the Y axis as calculated
        //        target->setPosition(
        //                            Point(winSize.width + (target->getContentSize().width),
        //                                CCDirector::getInstance()->getVisibleOrigin().y + actualY) );
        
        if(bus_flg){
            for (int i=0; i<5; i++) {
                target = Sprite::create("CD.png");
                target->setTag(1);
                target->setPosition(
                                    Point(winSize.width + (target->getContentSize().width),
                                          obli_cont) );
                
                //log("winSize.width %f + (target->getContentSize().width)%f  CCDirector::getInstance()->getVisibleOrigin().y %f¥n  actualY %d",winSize.width, (target->getContentSize().width),CCDirector::getInstance()->getVisibleOrigin().y, actualY);
                
                this->addChild(target);
                
                // Create the actions
                FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                              Point(0 - target->getContentSize().width, actualY+60*i) );
                target->runAction( CCSequence::create(actionMove, NULL) );
                if (i!=4) {
                    _targets.pushBack(target);
                }
            }
        }else if(hou_flg){
            target->setPosition(
                                Point(winSize.width + (target->getContentSize().width),
                                      player->getPositionY()) );
            
            //log("winSize.width %f + (target->getContentSize().width)%f  CCDirector::getInstance()->getVisibleOrigin().y %f¥n  actualY %d",winSize.width, (target->getContentSize().width),CCDirector::getInstance()->getVisibleOrigin().y, actualY);
            
            this->addChild(target);
            
            // Create the actions
            FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                          Point(0 - target->getContentSize().width, player->getPositionY()) );
            target->runAction( CCSequence::create(actionMove, NULL) );
        }else{
            target->setPosition(
                                Point(winSize.width + (target->getContentSize().width),
                                      obli_cont) );
            
            //log("winSize.width %f + (target->getContentSize().width)%f  CCDirector::getInstance()->getVisibleOrigin().y %f¥n  actualY %d",winSize.width, (target->getContentSize().width),CCDirector::getInstance()->getVisibleOrigin().y, actualY);
            
            this->addChild(target);
            
            // Create the actions
            FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                          Point(0 - target->getContentSize().width, actualY) );
            target->runAction( CCSequence::create(actionMove, NULL) );
        }
        
        //左から
    }else if (count == 1){
        
        // Create the target slightly off-screen along the right edge,
        // and along a random position along the Y axis as calculated
        //        target->setPosition(
        //                            Point(0,
        //                                CCDirector::getInstance()->getVisibleOrigin().y + actualY) );
        
        if(bus_flg){
            for (int i=0; i<5; i++) {
                target = Sprite::create("CD.png");
                target->setTag(1);
                
                target->setPosition(
                                    Point(0,
                                          obli_cont));
                
                target->setRotation(180);
                
                this->addChild(target);
                
                // Create the actions
                FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                              Point(winSize.width + target->getContentSize().width, actualY+60*i) );
                target->runAction( CCSequence::create(actionMove, NULL) );
                if (i!=4) {
                    _targets.pushBack(target);
                }
            }
        }else if(hou_flg){
            
            target->setPosition(
                                Point(0,
                                      player->getPositionY()));
            
            target->setRotation(180);
            
            this->addChild(target);
            
            // Create the actions
            FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                          Point(winSize.width + target->getContentSize().width, player->getPositionY()) );
            target->runAction( CCSequence::create(actionMove, NULL) );
        }else{
            
            target->setPosition(
                                Point(0,
                                      obli_cont));
            
            target->setRotation(180);
            
            this->addChild(target);
            
            // Create the actions
            FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                          Point(winSize.width + target->getContentSize().width, actualY) );
            target->runAction( CCSequence::create(actionMove, NULL) );
        }
        
        // 上から
    }else if (count == 2){
        
        if(bus_flg){
            for (int i=0; i<5; i++) {
                target = Sprite::create("CD.png");
                target->setTag(1);
                
                if (screenSize.height > 960)
                {
                    target->setPosition(
                                        Point(tate_count,
                                              840.0));
                }else{
                    target->setPosition(
                                        Point(tate_count,
                                              910.0));
                }
                
                target->setRotation(270);
                
                this->addChild(target);
                
                // Create the actions
                FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                              Point(actualX+i*60, 240 ));
                target->runAction( CCSequence::create(actionMove, NULL) );
                if (i!=4) {
                    _targets.pushBack(target);
                }
            }
        }else if(hou_flg){
            
            // Create the target slightly off-screen along the right edge,
            // and along a random position along the Y axis as calculated
            //        target->setPosition(
            //                            Point(actualX,
            //                                840.0));
            target->setPosition(
                                Point(player->getPositionX(),
                                      840.0));
            
            target->setRotation(270);
            
            this->addChild(target);
            
            // Create the actions
            FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                          Point(player->getPositionX(), 250 ));
            target->runAction( CCSequence::create(actionMove, NULL) );
        }else{
            
            // Create the target slightly off-screen along the right edge,
            // and along a random position along the Y axis as calculated
            //        target->setPosition(
            //                            Point(actualX,
            //                                840.0));
            target->setPosition(
                                Point(player->getPositionX(),
                                      840.0));
            
            target->setRotation(270);
            
            this->addChild(target);
            
            // Create the actions
            FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                          Point(actualX, 250 ));
            target->runAction( CCSequence::create(actionMove, NULL) );
        }
        
        // 下から
    }else if (count == 3){
        
        if(bus_flg){
            for (int i=0; i<5; i++) {
                target = Sprite::create("CD.png");
                target->setTag(1);
                target->setPosition(
                                    Point(tate_count,
                                          280.0));
                
                target->setRotation(90);
                
                this->addChild(target);
                
                if (screenSize.height > 960)
                {
                    // Create the actions
                    FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                                  Point(actualX+i*20, 1000 ));
                    target->runAction( CCSequence::create(actionMove, NULL) );
                }else{
                    // Create the actions
                    FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                                  Point(actualX+i*20, 1000 ));
                    target->runAction( CCSequence::create(actionMove, NULL) );
                }
                
                if (i!=4) {
                    _targets.pushBack(target);
                }
            }
        }else if(hou_flg){
            
            // Create the target slightly off-screen along the right edge,
            // and along a random position along the Y axis as calculated
            //        target->setPosition(
            //                            Point(actualX,
            //                                280.0));
            
            target->setPosition(
                                Point(player->getPositionX(),
                                      280.0));
            
            target->setRotation(90);
            
            this->addChild(target);
            
            
            if (screenSize.height > 960)
            {
                // Create the actions
                FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                              Point(player->getPositionX(), 900 ));
                target->runAction( CCSequence::create(actionMove, NULL) );
                
            }else{
                // Create the actions
                FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                              Point(player->getPositionX(), 1000 ));
                target->runAction( CCSequence::create(actionMove, NULL) );
            }
        }else{
            
            // Create the target slightly off-screen along the right edge,
            // and along a random position along the Y axis as calculated
            //        target->setPosition(
            //                            Point(actualX,
            //                                280.0));
            
            target->setPosition(
                                Point(tate_count,
                                      280.0));
            
            target->setRotation(90);
            
            if(pause_flg){
            this->addChild(target);
            
            if (screenSize.height > 960)
            {
                // Create the actions
                FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                              Point(actualX, 900 ));
                target->runAction( CCSequence::create(actionMove, NULL) );
            }else{
                // Create the actions
                FiniteTimeAction* actionMove = MoveTo::create( (float)actualDuration,
                                                              Point(actualX, 1000 ));
                target->runAction( CCSequence::create(actionMove, NULL) );
            }
            }
        }
    }
    
    
    //	FiniteTimeAction* actionMoveDone = CCCallFuncN::create( this,
    //                                            callfuncN_selector(HelloWorld::spriteMoveFinished));
    //	target->runAction( CCSequence::create(actionMove, actionMoveDone, NULL) );
    
    
    
    // Add to targets array
    _targets.pushBack(target);
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("投げる.mp3");
    bus_flg=false;
    hou_flg = false;
    }
}

void HelloWorld::spriteMoveFinished(Node* sender)
{
    Sprite *sprite = (Sprite *)sender;
    this->removeChild(sprite, true);
    
    if (sprite->getTag() == 1)  // target
    {
        _targets.eraseObject(sprite);
        
        GameOverScene *gameOverScene = GameOverScene::create();
        gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
        CCDirector::getInstance()->replaceScene(gameOverScene);
        
    }
    else if (sprite->getTag() == 2) // projectile
    {
        _projectiles.eraseObject(sprite);
    }
}

void HelloWorld::gameLogic(float dt)
{
    this->addTarget();
}

void HelloWorld::gameClear()
{
    GameOverScene *gameOverScene = GameOverScene::create();
    char a[100];
    int score = (int)elapsedTime*5+s_num*20+h_num*10;
    int bonus = 0;
    
    //log("~~~~~~~~~~%d",BEST_SCORE);
        BEST_SCORE = score;
        sprintf(a, "Score : %d\n BestScore : %d \n Update BEST SCORE!!",score,BEST_SCORE);
        gameOverScene->getLayer()->setScore(h_num, s_num, (int)elapsedTime, bonus, score, BEST_SCORE);
        log("heart %d, seii %d time %d, bonus %d,score %d, best %d",h_num, s_num, (int)elapsedTime, bonus, score, BEST_SCORE);
        userDefault = CCUserDefault::sharedUserDefault();
        int i = CCUserDefault::sharedUserDefault()->getIntegerForKey("integerKey",0);
        log("userdata best %d",i);
        userDefault->setIntegerForKey("integerKey", BEST_SCORE);
    //yo1->release();
    //yo2->release();
    //yo3->release();
    //yo4->release();
    if (season.compare("spring") == 0) {
        yo1->stopAllActions();
        yo2->stopAllActions();
        yo3->stopAllActions();
        yo4->stopAllActions();
    }
    //アニメーションを止める
    //gameOverScene->getLayer()->getLabel()->setString(a);
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    //CCCallFuncO *pFuncO = CCCallFuncO::create(this, callfuncO_selector(gameOverScene), score);
    CCDirector::getInstance()->replaceScene(gameOverScene);
}

void HelloWorld::gameOver()
{
    GameOverScene *gameOverScene = GameOverScene::create();
    char a[100];
    int score = (int)elapsedTime*5+s_num*20+h_num*10;
    int bonus = 0;
    
    //log("~~~~~~~~~~%d",BEST_SCORE);
        sprintf(a, "Score : %d\n BestScore : %d",score,BEST_SCORE);
        userDefault = CCUserDefault::sharedUserDefault();
        int i = CCUserDefault::sharedUserDefault()->getIntegerForKey("integerKey",0);
        gameOverScene->getLayer()->gameover();
        log("heart %d, seii %d time %d, bonus %d,score %d, best %d",h_num, s_num, (int)elapsedTime, bonus, score, BEST_SCORE);
        log("userdata %d",i);
    //yo1->release();
    //yo2->release();
    //yo3->release();
    //yo4->release();
    if (season.compare("spring") == 0) {
        yo1->stopAllActions();
        yo2->stopAllActions();
        yo3->stopAllActions();
        yo4->stopAllActions();
    }
    //アニメーションを止める
    //gameOverScene->getLayer()->getLabel()->setString(a);
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    //CCCallFuncO *pFuncO = CCCallFuncO::create(this, callfuncO_selector(gameOverScene), score);
    CCDirector::getInstance()->replaceScene(gameOverScene);
}

// cpp with cocos2d-x
void HelloWorld::onTouchEnded(Touch* touches, Event* event)
{
    
    //particle->setPosition(touches->getLocation().x, touches->getLocation().y);
    
    // Choose one of the touches to work with
    Touch* touch = touches;
    Point location = touch->getLocation();
    
    float loc_x = location.x;
    float loc_y = location.y;
    
    log("location %f, %f",loc_x, loc_y);
    
    if (location.x > CCDirector::getInstance()->getVisibleSize().width) {
        loc_x = CCDirector::getInstance()->getVisibleSize().width;
    }
    if (location.y > CCDirector::getInstance()->getVisibleSize().height) {
        loc_y = CCDirector::getInstance()->getVisibleSize().height;
    }
    
    Point ccp_loc = Point(loc_x, loc_y);
    
    Rect  rect1 = settoku1->boundingBox();
    Rect  rect2 = settoku2->boundingBox();
    Rect  rect3 = settoku3->boundingBox();
    Rect  rect4 = setsumon->boundingBox();
    
    
    
    Rect StatusRect = Rect(0,
                           900,
                           640,
                           1136);
    
    Rect RestartRect = Rect(550,
                            980,
                            120,
                            150);
    
    Rect KoukokuRect = Rect(0,
                            0,
                            640,
                            110);
    
    if(RestartRect.containsPoint(ccp_loc)){
        //log("touch");
        //CCDirector::getInstance()->replaceScene( HelloWorld::scene((char*)season->getCString()));
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CCDirector::getInstance()->replaceScene( TitleMenuScene::create() );
    
//            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
//            CCDirector::getInstance()->replaceScene( HelloWorld::scene(stage_num2 + 1));
        
//        if(!pause_flg){
//            pause_flg = true;
//            // 一時停止
//            cocos2d::Director::getInstance()->pause();
//            CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
//            for (auto* childs : this->getChildren()){
//                Sprite *spriteChilds = (Sprite *)childs;
//                spriteChilds->pause(); //———————–子供：ポーズ
//                for (auto* mago : spriteChilds->getChildren()){
//                    Sprite *spriteMagos = (Sprite *)mago;
//                    spriteMagos->pause();//——————–孫：ポーズ
//                    }
//            }
//        }else{
//            //一時停止を再開
//            cocos2d::Director::getInstance()->resume();
//            CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
//            for (auto* childs : this->getChildren()){
//                Sprite *spriteChilds = (Sprite *)childs;
//                spriteChilds->resume(); //———————–子供：ポーズ
//                for (auto* mago : spriteChilds->getChildren()){
//                    Sprite *spriteMagos = (Sprite *)mago;
//                    spriteMagos->resume(); //——————–孫：ポーズ
//                    }
//            }
//                        pause_flg = false;
//        }
    }
    
    
    if(rect1.containsPoint(ccp_loc)){
        
        //trueの場合に、何かしらの処理を行う
        //        log("++++++++touch settoku1");
        if (touch_flg) {
            AnserOutput(1);
        }
    }else if(rect2.containsPoint(ccp_loc)){
        
        //trueの場合に、何かしらの処理を行う
        //        log("++++++++touch settoku2");
        if (touch_flg) {
            AnserOutput(2);
        }
    }else if(rect3.containsPoint(ccp_loc)){
        
        //trueの場合に、何かしらの処理を行う
        //        log("++++++++touch settoku3");
        if (touch_flg) {
            AnserOutput(3);
        }
    }else if(rect4.containsPoint(ccp_loc)){
        
        //trueの場合に、何かしらの処理を行う
        //        log("++++++++touch settoku3");
        
    }else if(StatusRect.containsPoint(ccp_loc)){
        
        //trueの場合に、何かしらの処理を行う
        //        log("++++++++touch State");
    }else if(KoukokuRect.containsPoint(ccp_loc)){
    }else{
    
        
        //float duration =0.5f;
        //MoveTo* actionMove = MoveTo::create(duration, ccp_loc);
        
        //player->runAction(actionMove);
        
        //log("++++++++after  x:%f, y:%f", location.x, location.y);
        
        // Set up initial location of projectile
        Size winSize = CCDirector::getInstance()->getVisibleSize();
        Point origin = CCDirector::getInstance()->getVisibleOrigin();
        //Sprite *projectile = Sprite::create("naifu2.png", Rect(0, 0, 633, 561));
        //projectile->setScale(0.1);
        //projectile->setPosition( Point(origin.x+20, origin.y+winSize.height/2) );
        
        
        
        //アニメーションを止める
        player->stopActionByTag(1);
        player->stopActionByTag(2);
        
        //移動距離のx, y座標を求める
        float moveX = player->getPosition().x - location.x;
        float moveY = player->getPosition().y - location.y;
        
        //移動距離の絶対値を求める
        float absMoveX = abs((int)moveX);
        float absMoveY = abs((int)moveY);
        
        //移動距離を求める
        float distance = sqrtf(absMoveX + absMoveY);
        
        //移動先の指定距離によって時間を変更する
        MoveTo* move = MoveTo::create(distance / 20, Point(location.x,location.y));
        
        move->setTag(1);
        
        //アニメーションの作成
        Animation* animation = Animation::create();
        
        if (absMoveX < absMoveY && moveY > 0) {
            // 正面向きの4コマアニメーション
            animation->addSpriteFrameWithFile("スーツ_止１前.png");
            animation->addSpriteFrameWithFile("スーツ_走１前.png");
            animation->addSpriteFrameWithFile("スーツ_走２前.png");
        } else if (absMoveX < absMoveY && moveY < 0) {
            // 後ろ向きの4コマアニメーション
            animation->addSpriteFrameWithFile("スーツ_止１後.png");
            animation->addSpriteFrameWithFile("スーツ_走１後.png");
            animation->addSpriteFrameWithFile("スーツ_走２後.png");
        } else if (absMoveX > absMoveY && moveX > 0) {
            // 左向きの4コマアニメーション
            animation->addSpriteFrameWithFile("スーツ_止１左.png");
            animation->addSpriteFrameWithFile("スーツ_走１左.png");
            animation->addSpriteFrameWithFile("スーツ_走２左.png");
        } else {
            // 右向きの4コマアニメーション１
            animation->addSpriteFrameWithFile("スーツ_止１右.png");
            animation->addSpriteFrameWithFile("スーツ_走１右.png");
            animation->addSpriteFrameWithFile("スーツ_走２右.png");
        }
        
        //アニメーションの設定 1 : 1コマ0.1秒で切り替える。
        animation->setDelayPerUnit(0.1);
        
        //距離によってアニメーションのループ回数を変更する
        animation->setLoops(distance / 20 * 2.5 + 1);
        
        //アニメーションの設定
        Animate* animate = Animate::create(animation);
        animate->setTag(2);
        
        //アニメーションの実行
        player->runAction(animate);
        player->runAction(move);
        
        
        //        // Determinie offset of location to projectile
        //        float offX = location.x - projectile->getPosition().x;
        //        float offY = location.y - projectile->getPosition().y;
        //
        //        // Bail out if we are shooting down or backwards
        //        if (offX <= 0) return;
        //
        //        // Ok to add now - we've double checked position
        //        this->addChild(projectile);
        //
        //        // Determine where we wish to shoot the projectile to
        //        float realX = origin.x+winSize.width + (projectile->getContentSize().width/2);
        //        float ratio = offY / offX;
        //        float realY = (realX * ratio) + projectile->getPosition().y;
        //        Point realDest = Point(realX, realY);
        //
        //        // Determine the length of how far we're shooting
        //        float offRealX = realX - projectile->getPosition().x;
        //        float offRealY = realY - projectile->getPosition().y;
        //        float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));
        //        float velocity = 480/5; // 480pixels/1sec
        //        float realMoveDuration = length/velocity;
        //
        //        // Move projectile to actual endpoint
        //        projectile->runAction( CCSequence::create(
        //                                                  MoveTo::create(realMoveDuration, realDest),
        //                                                  CCCallFuncN::create(this,
        //                                                                      callfuncN_selector(HelloWorld::spriteMoveFinished)),
        //                                                  NULL) );
        //
        //        //Add to projectiles array
        //        projectile->setTag(2);
        //        _projectiles.pushBack(projectile);
        
        //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pew-pew-lei.wav");
        //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bgm_maoudamashii_orchestra12.mp3");
        
        
        //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pew-pew-lei.wav");
        //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bgm_maoudamashii_orchestra12.mp3");
    }
    //particle->setPosition(touch->getLocation().x, touch->getLocation().y);
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touches, cocos2d::Event *unused_event)
{
    Point location = touches->getLocationInView();
    location = CCDirector::getInstance()->convertToGL(location);
    log("%f %f" ,location.x, location.y);
    //this->resetMotionStreak();
    //CCPoint point = this->convertTouchToNodeSpace(touches);
    //this->addMotionStreakPoint(point);
    return true;
}

void HelloWorld::onTouchCancelled(cocos2d::Touch* touches, cocos2d::Event *unused_event)
{
}

void HelloWorld::onTouchMoved(cocos2d::Touch *pTouches, cocos2d::Event *pEvent) {
    
    Touch* touch = pTouches;
    
    Point location = touch->getLocationInView();
    location = CCDirector::getInstance()->convertToGL(location);
    log("%f %f" ,location.x, location.y);
    //CCPoint point = this->convertTouchToNodeSpace(pTouches);
    //this->addMotionStreakPoint(point);
}

Sprite *damage,*lifeup;



int tcount = 0;

void HelloWorld::updateGame(float dt)
{
    tcount++;
    
    /*CCProgressTimer* timer = (CCProgressTimer*)this->getChildByTag(1);
     float percent = timer->getPercentage();
     percent += 10.0f * dt;
     CCLOG("%f",percent);
     timer->setPercentage(percent);
     if (percent>100.0f) {
     this->unscheduleUpdate();
     }*/
    
    //CCArray *projectilesToDelete = new CCArray;
    //CCObject* it = NULL;
    //CCObject* jt = NULL;
    
    Rect playerRect = Rect(
                           player->getPosition().x - (player->getContentSize().width/2),
                           player->getPosition().y - (player->getContentSize().height/2),
                           player->getContentSize().width,
                           player->getContentSize().height);
    
    //particle->setPosition(player->getPosition().x,player->getPosition().y);
    
    if((clear_seii[bgm_num] != 0) && s_num == clear_seii[bgm_num])
    {
        gameClear();
    }
    if ((clear_time[bgm_num] != 0) && (int)elapsedTime >= clear_time[bgm_num]/cleartime_mod) {
        gameClear();
    }
    
    if (season.compare("spring") == 0) {
        //log("%i", seasons);
        
        if(yo1->boundingBox().intersectsRect(playerRect)){
            Texture2D *pTexture = TextureCache::sharedTextureCache()->addImage(yopparai3_png);
            // spriteTestにセット
            yo1->setTexture(pTexture);
        }else if(yo2->boundingBox().intersectsRect(playerRect)){
            Texture2D *pTexture = TextureCache::sharedTextureCache()->addImage(yopparai3_png);
            // spriteTestにセット
            yo2->setTexture(pTexture);
        }
        else if (yo3->boundingBox().intersectsRect(playerRect)){
            Texture2D *pTexture = TextureCache::sharedTextureCache()->addImage(yopparai3_png);
            // spriteTestにセット
            yo3->setTexture(pTexture);
        }
        else if (yo4->boundingBox().intersectsRect(playerRect)){
            Texture2D *pTexture = TextureCache::sharedTextureCache()->addImage(yopparai3_png);
            // spriteTestにセット
            yo4->setTexture(pTexture);
        }
    }
    
    if(_targets.size() >0){
        for(auto jt = _targets.begin();jt != _targets.end(); jt++)
        {
            Vector<Sprite*> targetsToDelete;
            Sprite* target = (*jt);
            
            // if (Rect::RectIntersectsRect(projectileRect, targetRect))
            //            if (projectileRect.intersectsRect(targetRect))
            //			{
            //				targetsToDelete.pushBack(target);
            //			}
            
            //log("%d %d",player->getPosition().x, player->getPosition().y);
            
            
            if (target != NULL   ){
                
            if(target->boundingBox().intersectsRect(playerRect))
            {

                if (target->getTag() == 999) {
                    if(!lifeup_flg){
                        if (h_num < LIFE_MAX) {
                            h_num++;
                            lifeup = Sprite::create("アイコン-欲しがり屋さん.png");
                            lifeup->setPosition(Point(player->getPositionX(), player->getPositionY()));
                            this->scheduleOnce(schedule_selector(HelloWorld::removeDamage), 0.5);
                            lifeup_flg = true;
                            this->addChild(lifeup,3,998);
                            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("おにぎり.mp3");
                        }
                    }
                }else if(!cd_flg){
                    int touch = target->getTag();
                    h_num = h_num-touch;
                    if (h_num < 0) {
                        h_num = 0;
                    }
                    
                    switch (touch) {
                        case 1:
                            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("当たる（軽）.mp3");
                            damage = Sprite::create("ダメージ１.png");
                            break;
                        case 2:
                            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("当たる（割）.mp3");
                            damage = Sprite::create("ダメージ２.png");
                            break;
                        case 3:
                            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("当たる（重）.mp3");
                            damage = Sprite::create("ダメージ３.png");
                            break;
                        case 4:
                            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("当たる（刺）.mp3");
                            damage = Sprite::create("ダメージ３.png");
                            break;
                            
                        default:
                            break;
                    }
                    damage->setPosition(Point(player->getPositionX(), player->getPositionY()));
                    this->scheduleOnce(schedule_selector(HelloWorld::removeDamage), 0.5);

                    cd_flg = true;
                    this->addChild(damage,3,101);
                    
                    //log("~~~~~~~~~~~tag %d ",target->getTag());
                    if (h_num < 1) {
                        gameOver();
                    }
                }else{
                    damage->setPosition(Point(player->getPositionX(), player->getPositionY()));
                }


                
                //heart
                lifeOutput();
                //targetsToDelete.pushBack(target);
            }
            
                    if (target->getPositionX() < 0 || target->getPositionX() > 1040 || target->getPositionY() < 280 || target->getPositionY() > 880) {
                        if (screenSize.height > 960)
                        {
            
                            if (target->getPositionY() < 270 || target->getPositionY() > 880) {
            
                                targetsToDelete.pushBack(target);
                            }
                        }else{
                            if (target->getPositionY() < 260 || target->getPositionY() > 930) {
            
                                targetsToDelete.pushBack(target);
                                log("++++++++++++++++");
                            }
                        }
            
                        for (auto jt = targetsToDelete.begin(); jt != targetsToDelete.end(); jt++)
                        {
                            Sprite *target = (*jt);
                            _targets.eraseObject(target);
                            this->removeChild(target, true);
            
//            _projectilesDestroyed++;
//            			if (_projectilesDestroyed >= 5)
//            			{
//            				GameOverScene *gameOverScene = GameOverScene::create();
//            				gameOverScene->getLayer()->getLabel()->setString("You Win!");
//            				CCDirector::getInstance()->replaceScene(gameOverScene);
//            			}
                        }
                    }
            
                        //targetsToDelete.clear();
        }
    }
    
    //    CCARRAY_FOREACH(_projectiles, it)
    //    {
    //        CCArray* targetsToDelete =new CCArray;
    //        Sprite *target = dynamic_cast<Sprite*>(it);
    //        Rect playerRect = Rect(
    //                                       player->getPosition().x - (player->getContentSize().width/2),
    //                                       player->getPosition().y - (player->getContentSize().height/2),
    //                                       player->getContentSize().width,
    //                                       player->getContentSize().height);
    //
    //        if (target->boundingBox().intersectsRect(playerRect))
    //        {
    //            h_num--;
    //            if (h_num < 1) {
    //                gameOver();
    //            }
    //            //heart
    //            lifeOutput();
    //            targetsToDelete.pushBack(target);
    //        }
    //
    //        CCARRAY_FOREACH(targetsToDelete, it)
    //		{
    //			Sprite *target = dynamic_cast<Sprite*>(it);
    //			_projectiles->removeObject(target);
    //			this->removeChild(target, true);
    //
    //			_projectilesDestroyed++;
    //
    //		}
    //
    //		targetsToDelete->release();
    //    }
    
    
    // for (it = _projectiles->begin(); it != _projectiles->end(); it++)
    //    CCARRAY_FOREACH(_projectiles, it)
    //	{
    //		Sprite *projectile = dynamic_cast<Sprite*>(it);
    //		Rect projectileRect = Rect(
    //                                           projectile->getPosition().x - (projectile->getContentSize().width/2),
    //                                           projectile->getPosition().y - (projectile->getContentSize().height/2),
    //                                           projectile->getContentSize().width,
    //                                           projectile->getContentSize().height);
    //
    //		CCArray* targetsToDelete =new CCArray;
    //
    //		// for (jt = _targets->begin(); jt != _targets->end(); jt++)
    //        CCARRAY_FOREACH(_targets, jt)
    //		{
    //			Sprite *target = dynamic_cast<Sprite*>(jt);
    //			Rect targetRect = Rect(
    //                                           target->getPosition().x - (target->getContentSize().width/2),
    //                                           target->getPosition().y - (target->getContentSize().height/2),
    //                                           target->getContentSize().width,
    //                                           target->getContentSize().height);
    //
    //			// if (Rect::RectIntersectsRect(projectileRect, targetRect))
    ////            if (projectileRect.intersectsRect(targetRect))
    ////			{
    ////				targetsToDelete.pushBack(target);
    ////			}
    //
    //            //log("%d %d",player->getPosition().x, player->getPosition().y);
    //
    //            if (player->boundingBox().intersectsRect(targetRect))
    //            {
    //                h_num--;
    //                if (h_num < 1) {
    //                    GameOverScene *gameOverScene = GameOverScene::create();
    //                    //gameOverScene->getLayer()->getLabel()->setString("You Win!");
    //                    CCDirector::getInstance()->replaceScene(gameOverScene);
    //                }
    //                //heart
    //                lifeOutput();
    //                targetsToDelete.pushBack(target);
    //                log("Touch Ossan+++++++++");
    //            }
    //		}
    //
    //		// for (jt = targetsToDelete->begin(); jt != targetsToDelete->end(); jt++)
    //        CCARRAY_FOREACH(targetsToDelete, jt)
    //		{
    //			Sprite *target = dynamic_cast<Sprite*>(jt);
    //			_targets->erace(target);
    //			this->removeChild(target, true);
    //
    //			_projectilesDestroyed++;
    //            //			if (_projectilesDestroyed >= 5)
    //            //			{
    //            //				GameOverScene *gameOverScene = GameOverScene::create();
    //            //				gameOverScene->getLayer()->getLabel()->setString("You Win!");
    //            //				CCDirector::getInstance()->replaceScene(gameOverScene);
    //            //			}
    //		}
    //
    //		if (targetsToDelete->count() > 0)
    //		{
    //			projectilesToDelete.pushBack(projectile);
    //		}
    //		targetsToDelete->release();
    //	}
    //
    //	// for (it = projectilesToDelete->begin(); it != projectilesToDelete->end(); it++)
    //    CCARRAY_FOREACH(projectilesToDelete, it)
    //	{
    //		Sprite* projectile = dynamic_cast<Sprite*>(it);
    //		_projectiles->removeObject(projectile);
    //		this->removeChild(projectile, true);
    //	}
    //	projectilesToDelete->release();
    }
    
    elapsedTime += dt;
    
    //時間を表示する
    CCString* timeString = CCString::createWithFormat("%8.0f", elapsedTime);
    LabelTTF* timerLabel = (LabelTTF*)this->getChildByTag(100);
    timerLabel->setString(timeString->getCString());
    
    seasons = stage_num2;
    
    if (seasons == 15 || seasons == 16 || seasons == 17) {
        if ((int)(elapsedTime*10) % 20 == 0 && (int)elapsedTime % 14 == 0) {
            trap(seasons);
        }
    }
    
    if (seasons == 21 || seasons == 22 || seasons == 23) {
        if ((int)(elapsedTime*10) % 10 == 0 && (int)elapsedTime % 7 == 0) {
            trap(seasons);
        }
    }
    
//    if (elapsedTime > cleartime) {
//        gameOver();
//    }
    
    //SCOREを表示する
//    CCString* scoreString = CCString::createWithFormat("%8.0d", (int)elapsedTime*5+s_num*20);
//    LabelTTF* scoreLabel = (LabelTTF*)this->getChildByTag(200);
//    scoreLabel->setString(scoreString->getCString());
}

void HelloWorld::trap(int seasons)
{
    if (seasons <= 17) {
        Sprite* otiba = Sprite::create(otiba_png);
        otiba->setPosition(Point(600,960));
        this->addChild(otiba);
        
        //Animation( *animation = Animation(::create();
        
        otiba->runAction(MoveTo::create(5.0f, Point(0,-500)));
        
        //        Animate *action = Animate::create(animation);
        //        CCRepeatForever *anime = CCRepeatForever::create(action);
        //        otiba->runAction(anime);
    } else if (seasons >= 21) {
        Sprite* hubuki = Sprite::create(hubuki_png);
        hubuki->setPosition(Point(-900,580));
        this->addChild(hubuki);
        
        hubuki->runAction(MoveTo::create(5.0f, Point(1500,580)));
    }
}

void HelloWorld::removeDamage(float dt)
{
    if(cd_flg){
        cd_flg = false;
        this->removeChildByTag(101);
    }else if(lifeup_flg){
        lifeup_flg = false;
        this->removeChildByTag(998);
    }
}

int MOTION_STREAK_TAG = 8000;
int m_iCount = 0;
void HelloWorld::onEnter() {
    CCNode::onEnter();
    this->setTouchEnabled(true);
    //CCDirector::getInstance()->gett getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}

void HelloWorld::resetMotionStreak() {
    this->removeChildByTag(MOTION_STREAK_TAG, true);
    CCMotionStreak* streak = CCMotionStreak::create(0.5f, 1, 10, ccc3(255, 255, 0), "line.png");
    this->addChild(streak, 5, MOTION_STREAK_TAG);
}

void HelloWorld::addMotionStreakPoint(cocos2d::CCPoint point) {
    CCMotionStreak* streak = (CCMotionStreak*)this->getChildByTag(MOTION_STREAK_TAG);
    streak->setPosition(point);
    
    if (++m_iCount>100) {
        int r = rand()%256;
        int b = rand()%265;
        int g = rand()%256;
        streak->setColor(ccc3(r, b, g));
        m_iCount = 0;
    }
}

//void HelloWorld::registerWithTouchDispatcher()
//{
//	// TouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
//    CCDirector::getInstance()->getTouchDispatcher()->addStandardDelegate(this,0);
//}
