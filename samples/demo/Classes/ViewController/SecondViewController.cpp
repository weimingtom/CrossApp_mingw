#include "SecondViewController.h"

#define CAColor_blueStyle ccc4(51,204,255,255)

#define CELL_COUNT 16

SecondViewController::SecondViewController() :
isPullUpRefresh(true)
{
	for (int i = 0; i < NUM; i++)
	{
		sect[i] = CELL_COUNT;
	}
}

SecondViewController::~SecondViewController()
{
	//personList.clear();
}

void SecondViewController::viewDidLoad(void)
{	
	loadJsonData();

	CAPullToRefreshView* headerRefreshView = CAPullToRefreshView::create(CAPullToRefreshView::CAPullToRefreshTypeHeader);
	CAPullToRefreshView* footerRefreshView = CAPullToRefreshView::create(CAPullToRefreshView::CAPullToRefreshTypeFooter);

	p_TableView = CATableView::createWithFrame(this->getView()->getBounds());
	p_TableView->setTableViewDataSource(this);
	p_TableView->setTableViewDelegate(this);
	p_TableView->setAllowsSelection(true);
	p_TableView->setScrollViewDelegate(this);
	p_TableView->setHeaderRefreshView(headerRefreshView);
	p_TableView->setFooterRefreshView(footerRefreshView);
	this->getView()->addSubview(p_TableView);
}

void SecondViewController::viewDidAppear()
{
	CANavigationBarItem* item = CANavigationBarItem::create("ViewController2");
	this->getTabBarController()->setNavigationBarItem(item);
}

void SecondViewController::loadJsonData()
{

}

void SecondViewController::viewDidUnload()
{
	
}

void SecondViewController::reshapeViewRectDidFinish()
{

}

void SecondViewController::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	
}

void SecondViewController::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{

}

CATableViewCell* SecondViewController::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
	CATableViewCell* cell = table->dequeueReusableCellWithIdentifier("CrossApp");
	return cell;

}

CAView* SecondViewController::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
	CADipSize _viewSize = viewSize;
	char head[10] = "";
	CAView* view = CAView::createWithColor(ccc4(239,242,243,255));
	CAButton* headControl1 = CAButton::createWithCenter(CADipRect(60, _viewSize.height*0.5, 80, 80),
		CAButtonTypeRoundedRect);
	headControl1->setTag(100 + (int)section);
	if (sect[section] == CELL_COUNT)
	{
		headControl1->setBackGroundViewForState(CAControlStateNormal, CAImageView::createWithImage(CAImage::create("source_material/close1.png")));
	}
	else
	{
		headControl1->setBackGroundViewForState(CAControlStateNormal, CAImageView::createWithImage(CAImage::create("source_material/open1.png")));
	}
	headControl1->addTarget(this, CAControl_selector(SecondViewController::switchCellListInSection), CAControlEventTouchUpInSide);
	view->addSubview(headControl1);

	CALabel* header = CALabel::createWithCenter(CADipRect(_viewSize.width*0.5, _viewSize.height*0.5, 300, 50));
	sprintf(head, "Section-%d", section);
	header->setFontSize(_px(30));
	header->setText(head);
	header->setColor(CAColor_blueStyle);
	header->setTextAlignment(CATextAlignmentCenter);
	header->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	view->addSubview(header);

	return view;
}

CAView* SecondViewController::tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
	CADipSize _viewSize = viewSize;
	char head[10] = "";
	CAView* view = CAView::createWithColor(CAColor_blueStyle);
   
	return view;
}

unsigned int SecondViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	return sect[section];
}

unsigned int SecondViewController::numberOfSections(CATableView *table)
{
	return NUM;
}

unsigned int SecondViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	return _px(100);
}

unsigned int SecondViewController::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
	return _px(100);
}

unsigned int SecondViewController::tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
{
	return 1;
}

void SecondViewController::scrollViewHeaderBeginRefreshing(CAScrollView* view)
{
	isPullUpRefresh = true;
	CAScheduler::schedule(schedule_selector(SecondViewController::refreshTableViewData), this, 0.1, 0, CCRANDOM_0_1() * 2, false);
}

void SecondViewController::scrollViewFooterBeginRefreshing(CAScrollView* view)
{
	isPullUpRefresh = false;
	CAScheduler::schedule(schedule_selector(SecondViewController::refreshTableViewData), this, 0.1, 0, CCRANDOM_0_1() * 2, false);
}

void SecondViewController::refreshTableViewData(float interval)
{
	for (int i = 0; i < NUM; i++)
	{
		sect[i] = (isPullUpRefresh == true) ? 0 : CELL_COUNT;
	}
	p_TableView->reloadData();
}

void SecondViewController::switchCellListInSection(CAControl* btn, CCPoint point)
{
	int section = btn->getTag() - 100;
	CC_RETURN_IF(section >= NUM);
	sect[section] = sect[section] ? 0 : CELL_COUNT;
	btn->retain()->autorelease();
	p_TableView->reloadData();
}

void SecondViewController::closeCellListInSection(CAControl* btn, CCPoint point)
{

}
