package com.ceovision.bonita.actorfilter;

import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

import org.bonitasoft.engine.api.IdentityAPI;
import org.bonitasoft.engine.connector.ConnectorValidationException;
import org.bonitasoft.engine.filter.AbstractUserFilter;
import org.bonitasoft.engine.filter.UserFilterException;
import org.bonitasoft.engine.identity.User;
import org.bonitasoft.engine.identity.UserSearchDescriptor;
import org.bonitasoft.engine.search.SearchOptionsBuilder;
import org.bonitasoft.engine.search.SearchResult;

public class FilterByUserOrUserlist extends AbstractUserFilter {

    Logger logger= Logger.getLogger("org.bonitasoft");

    static final String USERNAME_INPUT = "username";
    String username;

    /**
     * Perform validation on the inputs defined on the actorfilter definition (src/main/resources/bonita-actorfilter-filter-by-user-or-userlist.def)
     * You should: 
     * - validate that mandatory inputs are presents
     * - validate that the content of the inputs is coherent with your use case (e.g: validate that a date is / isn't in the past ...)
     */
    @Override
    public void validateInputParameters() throws ConnectorValidationException {
        checkNonEmptyStringInput(USERNAME_INPUT);
    }

    protected void checkNonEmptyStringInput(String inputName) throws ConnectorValidationException {
        try {
            String value = (String) getInputParameter(inputName);
            if (value == null || value.trim().isEmpty()) {
                throw new ConnectorValidationException(String.format("Mandatory parameter '%s' must not be empty", inputName));
            }
            username = value;
        } catch (ClassCastException e) {
            throw new ConnectorValidationException(String.format("'%s' parameter must be a String", inputName));
        }
    }

    /**
     * @return a list of {@link User} id that are the candidates to execute the task where this filter is defined. 
     * If the result contains a unique user, the task will automaticaly be assigned.
     * @see AbstractUserFilter.shouldAutoAssignTaskIfSingleResult
     */
    @Override
    public List<Long> filter(String actorName) throws UserFilterException {
        List<Long> users = new ArrayList<Long>();
        IdentityAPI identityApi = getAPIAccessor().getIdentityAPI();
        try {
            if (username.startsWith("ul_")) {
                SearchOptionsBuilder searchBuilder = new SearchOptionsBuilder(0, 100);
                searchBuilder.filter(UserSearchDescriptor.GROUP_ID, identityApi.getGroupByPath(username).getId());
                SearchResult<User> searchedUsers = identityApi.searchUsers(searchBuilder.done());
                for (User userAux: searchedUsers.getResult()) {
                    users.add(userAux.getId());
                }
            } else {
                if (username.contains("|")) {
                    username = "admin";
                }
                User targetUser = identityApi.getUserByUserName(username);
                users.add(targetUser.getId());
            }
        } catch (Exception e) {
            logger.severe("ERROR during actor filter" + e.getMessage());
        }
        return users;
    }
}