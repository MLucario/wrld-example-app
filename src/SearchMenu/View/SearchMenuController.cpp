// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuController.h"

#include "TagSearchRepository.h"
#include "IMenuOption.h"
#include "IModalBackgroundView.h"
#include "ISearchMenuView.h"
#include "SearchQuery.h"
#include "SearchResultModel.h"
#include "SearchResultViewClearedMessage.h"
#include "SwallowSearchConstants.h"
#include "SearchQueryResultsRemovedMessage.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchMenuController::SearchMenuController(Menu::View::IMenuModel& model,
                                                       Menu::View::IMenuViewModel& viewModel,
                                                       Menu::View::IMenuView& view,
                                                       ISearchMenuView& searchMenuView,
                                                       Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                                       TagSearch::View::ITagSearchRepository& tagSearchRepository,
                                                       Modality::View::IModalBackgroundView& modalBackgroundView,
                                                       ExampleAppMessaging::TMessageBus& messageBus)
            : Menu::View::MenuController(model, viewModel, view, messageBus)
            , m_searchMenuView(searchMenuView)
            , m_searchSectionViewModel(searchSectionViewModel)
            , m_tagSearchRepository(tagSearchRepository)
            , m_modalBackgroundView(modalBackgroundView)
            , m_messageBus(messageBus)
            , m_appModeAllowsOpen(true)
            , m_lastPerformedQuery(Search::SdkModel::SearchQuery("", false, false, Eegeo::Space::LatLongAltitude(0, 0, 0), 0))
            , m_onSearchItemAddedCallback(this, &SearchMenuController::OnSearchItemAdded)
            , m_onSearchItemRemovedCallback(this, &SearchMenuController::OnSearchItemRemoved)
            , m_onOpenStateChangedCallback(this, &SearchMenuController::OnOpenStateChanged)
            , m_performedQueryHandler(this, &SearchMenuController::OnSearchQueryPerformedMessage)
            , m_receivedQueryResponseHandler(this, &SearchMenuController::OnSearchQueryResponseReceivedMessage)
            , m_receivedQueryResultsRemovedHandler(this, &SearchMenuController::OnSearchQueryResultsRemovedMessage)
            , m_onSearchCallback(this, &SearchMenuController::OnSearch)
            , m_onSearchClearedCallback(this, &SearchMenuController::OnSearchCleared)
            , m_onSearchItemSelectedCallback(this, &SearchMenuController::OnSearchItemSelected)
            , m_onModalBackgroundTappedCallback(this, &SearchMenuController::OnModalBackgroundTapped)
            {
                m_searchMenuView.InsertSearchPeformedCallback(m_onSearchCallback);
                m_searchMenuView.InsertSearchClearedCallback(m_onSearchClearedCallback);
                m_searchMenuView.InsertSearchItemSelectedCallback(m_onSearchItemSelectedCallback);
                
                Menu::View::IMenuModel& searchSectionMenuModel = m_searchSectionViewModel.GetModel();
                searchSectionMenuModel.InsertItemAddedCallback(m_onSearchItemAddedCallback);
                searchSectionMenuModel.InsertItemRemovedCallback(m_onSearchItemRemovedCallback);
                
                m_viewModel.InsertOpenStateChangedCallback(m_onOpenStateChangedCallback);
                m_modalBackgroundView.InsertTappedCallback(m_onModalBackgroundTappedCallback);
                
                m_messageBus.SubscribeUi(m_performedQueryHandler);
                m_messageBus.SubscribeUi(m_receivedQueryResponseHandler);
                m_messageBus.SubscribeUi(m_receivedQueryResultsRemovedHandler);

                const size_t numSections = m_viewModel.SectionsCount();
                std::vector<Menu::View::IMenuSectionViewModel*> sections;
                sections.reserve(numSections);

                for (size_t groupIndex = 0; groupIndex < numSections; groupIndex++)
                {
                    auto& section = m_viewModel.GetMenuSection(static_cast<int>(groupIndex));
                    sections.push_back(&section);
                }
                
                m_searchMenuView.SetMenuSections(sections);
            }
            
            SearchMenuController::~SearchMenuController()
            {
                m_messageBus.UnsubscribeUi(m_receivedQueryResultsRemovedHandler);
                m_messageBus.UnsubscribeUi(m_receivedQueryResponseHandler);
                m_messageBus.UnsubscribeUi(m_performedQueryHandler);
                
                m_modalBackgroundView.RemoveTappedCallback(m_onModalBackgroundTappedCallback);
                m_viewModel.RemoveOpenStateChangedCallback(m_onOpenStateChangedCallback);
                
                Menu::View::IMenuModel& searchSectionMenuModel = m_searchSectionViewModel.GetModel();
                searchSectionMenuModel.RemoveItemRemovedCallback(m_onSearchItemRemovedCallback);
                searchSectionMenuModel.RemoveItemAddedCallback(m_onSearchItemAddedCallback);
                
                m_searchMenuView.RemoveSearchItemSelectedCallback(m_onSearchItemSelectedCallback);
                m_searchMenuView.RemoveSearchClearedCallback(m_onSearchClearedCallback);
                m_searchMenuView.RemoveSearchPeformedCallback(m_onSearchCallback);
            }
            
            void SearchMenuController::OnSearchItemAdded(Menu::View::MenuItemModel& item)
            {
                m_presentationDirty = true;
            }
            
            void SearchMenuController::OnSearchItemRemoved(Menu::View::MenuItemModel& item)
            {
                m_presentationDirty = true;
            }
            
            void SearchMenuController::OnOpenStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState)
            {
                if(openState != 1.f)
                {
                    m_searchMenuView.RemoveSeachKeyboard();
                }
            }
            
            void SearchMenuController::OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message)
            {
                std::string headerString = TagSearch::View::GetPresentationStringForQuery(m_tagSearchRepository, message.Query());
                
                if(Search::Swallow::SearchConstants::ShouldShowTagAsSearchResult(message.Query().Query()))
                {
                    m_searchMenuView.SetEditText(headerString, message.Query().IsTag());
                    m_searchMenuView.SetSearchInProgress(true);
                }

                m_lastPerformedQuery = message.Query();
            }
            
            void SearchMenuController::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
				if (message.GetResults().size() <= 0)
				{
					m_messageBus.Publish(SearchResultSection::SearchResultViewClearedMessage());
				}

                m_searchMenuView.CollapseAll();
                m_searchMenuView.SetSearchInProgress(false);
                
                int resultCount = static_cast<int>(message.GetResults().size());
                
                if(resultCount > 0)
                {
                    for(std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = message.GetResults().begin(); it != message.GetResults().end(); ++it)
                    {
                        if(!Search::Swallow::SearchConstants::ShouldShowTagAsSearchResult((*it).GetPrimaryTag()))
                        {
                            --resultCount;
                            
                            if(resultCount == 0)
                            {
                                break;
                            }
                        }
                    }
                }
                
                m_searchMenuView.SetSearchResultCount(resultCount);
            }

            void SearchMenuController::OnSearchQueryResultsRemovedMessage(const Search::SearchQueryResultsRemovedMessage& message)
            {
                m_searchMenuView.RemoveSearchQueryResults();
            }
            
            void SearchMenuController::OnSearch(const std::string& searchQuery)
            {
                m_messageBus.Publish(SearchMenuPerformedSearchMessage(searchQuery, false, false));
            }
            
            bool SearchMenuController::TryDrag()
            {
                return MenuController::TryDrag();
            }
            
            void SearchMenuController::OnViewClicked()
            {
                if(IsFullyOpen() && m_searchMenuView.GetEditText().length() > 0)
                {
                    m_messageBus.Publish(SearchMenuPerformedSearchMessage(m_searchMenuView.HasTagSearch() ? m_lastPerformedQuery.Query() : m_searchMenuView.GetEditText(),
                                                                          m_searchMenuView.HasTagSearch(),
                                                                          m_searchMenuView.HasTagSearch() ? m_lastPerformedQuery.ShouldTryInteriorSearch() : false));
                }
                else
                {
                    MenuController::OnViewClicked();
                }
            }
            
            void SearchMenuController::OnSearchCleared()
            {
                m_searchMenuView.HideSearchResultCount();
                
                m_messageBus.Publish(SearchResultSection::SearchResultViewClearedMessage());
            }
            
            void SearchMenuController::OnSearchItemSelected(int& index)
            {
                m_searchSectionViewModel.GetItemAtIndex(index).MenuOption().Select();
            }
            
            void SearchMenuController::OnModalBackgroundTapped()
            {
                if(!m_appModeAllowsOpen)
                {
                    return;
                }
                
                if(m_viewModel.IsFullyOpen() && !m_view.IsAnimating())
                {
                    m_viewModel.Close();
                }
            }
            
            void SearchMenuController::RefreshPresentation(bool forceRefresh)
            {
                MenuController::RefreshPresentation(forceRefresh);
                
                if(!m_viewModel.IsFullyClosed())
                {
                    m_searchMenuView.SetSearchSection(m_searchSectionViewModel);
                }
            }

            bool SearchMenuController::IsFullyOpen() const
            {
                return m_viewModel.IsFullyOpen();
            }

            void SearchMenuController::UpdateOpenState()
            {
                m_viewModel.UpdateOpenState(1.0f);
            }
        }
    }
}